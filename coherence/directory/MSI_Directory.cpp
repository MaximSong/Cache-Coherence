#include "Directory_Controller.h"
#include "sim.h"

void DirectoryController::MSI_tick()
{
    Request *request;
    dir_entry_t *entry;

    if (!request_in_progress)
    {
        if (((request = poll_queue()) != NULL))
        {
            entry = get_entry(request->block);

            debug_printf("\t\tProcessing req from node %lu for block 0x%lx, state: %s, msg: %s\n", request->srcID,
                         request->block, dir_state_t_str[entry->state], message_t_str[request->msg]);

            // Directories for all protocols follow a similar pattern where the state machine is implemented as a series
            // of if-then-else statements. The current state of the block (entry->state) in addition to the request
            // message type (request->msg) are examined to check the current state, and take actions based on the
            // message type including setting the next state of the entry and take any network actions as required.

            if (entry->state == I && request->msg == GETM)
            {
                // TODO: Fill me in

                // Set the request_in_progress flag since the directory stalls until the memory response comes back
                entry->state = M;
                entry->presence[request->srcID] = true;
                entry->active_sharers++;
                request_in_progress = true;
                // Memory response will come back at current clock time + memory access latency
                response_time = Global_Clock + mem_latency;
                // Entry will be in state M once the data comes back from main memory

                // Requesting processor's presence bit is set and number of active sharers incremented
                tag_to_send = request->block;
                target_node = request->srcID;
                debug_printf("\t\t\tRequesting data from memory\n");
                // sim->memory_reads++;
                //  Remove request from the head of the request queue
                dequeue();
            }
            else if (entry->state == I && request->msg == GETS)
            {
                // TODO: Fill me in

                // requesting data from memory. directory stalls till memory response
                // once memory response comes in, we will be in S
                entry->state = S;
                entry->presence[request->srcID] = true;
                entry->active_sharers++;
                request_in_progress = true;
                response_time = Global_Clock + mem_latency;
                tag_to_send = request->block;
                target_node = request->srcID;
                debug_printf("\t\t\tRequesting data from memory\n");

                // very similar to the GETM case

                // debug_printf("\t\t\tRequesting data from memory\n");
                // Remove request from the head of the request queue
                // sim->memory_reads++;
                dequeue();
            }
            else if (entry->state == M && request->msg == GETM)
            {
                // TODO: Fill me in

                // The block is in M state, and an agent issues a store (GETM) request. The directory will recall data
                // from the agent that currently has the block in the dirty state before sending it to the requesting
                // agent.

                // debug_printf("\t\t\tNode %d will provide data for $-$ transfer\n", <var>);

                // Send a data recall to the target agent in order to get the current dirty block from the agent. Tell
                // the agent to go to I state since the request is a write to the block. Then move the current state
                // from M to MM since the block is moving from M to M but the agent in the M state is changing and needs
                // to be sent the recalled data
                tag_to_send = request->block;
                target_node = UINT64_MAX;
                for (nodeID_t i = 0; i < settings.num_procs; i++)
                {
                    if (entry->presence[i])
                    {
                        target_node = i;
                        debug_printf("\t\t\tNode %lu will provide data for $-$ transfer\n", i);
                    }
                }

                // The requester now becomes the new owner with the block in the 'M' state.
                debug_printf("\t\t\tRecall_goto_I: ");
                send_Request(target_node, tag_to_send, RECALL_GOTO_I);
                entry->state = MM;
                entry->req_node_in_transient = request->srcID;

                dequeue();
            }
            else if (entry->state == M && request->msg == GETS)
            {
                // TODO: Fill me in
                // The block is in the M state, and an agent issues a read (GETS). The directory will recall the data
                // from the agent that currently has the block in the dirty state before sending it to the requesting
                // agent.
                tag_to_send = request->block;
                target_node = UINT64_MAX;
                for (nodeID_t i = 0; i < settings.num_procs; i++)
                {
                    if (entry->presence[i])
                    {
                        target_node = i;
                        entry->O_F_id = i;
                        debug_printf("\t\t\tNode %d will go to O and provide data for $-$ transfer\n", i);
                    }
                }
                debug_printf("\t\t\tRecall_goto_S: ");
                send_Request(target_node, tag_to_send, RECALL_GOTO_S);
                entry->state = MS;
                entry->req_node_in_transient = request->srcID;

                // Send a data recall to the target agent in order to get the current dirty block from the agent. Tell
                // the agent to go to S state since the request is a read. Then move the current state
                // from M to MS since the block is moving from M to S but needs to wait on the data from the target
                // agent before providing it to the requesting agent.

                // Remove request from the head of the request queue
                dequeue();
            }
            else if (entry->state == MM && request->msg == DATA)
            {
                // TODO: Fill me in
                // Current state is MM and the message is DATA. This means that the data can be sent to the agent that
                // requested the data and the block state can move to M.
                // The target node is the one that had made the request when the block was in the MM state.
                // now that the original in M has gone to the I state remove it's presence bit
                // Directory serves as $-$ transfer agent: Increment stats!
                // sim->memory_reads++;
                //  Memory is updated since the original agent left the M state
                // debug_printf("\t\t\tCache to cache transfer via directory: ");
                // Set the block's state to M and set the presence bit for the processor that now has the block in M.
                // Remove request from the head of the request queue
                tag_to_send = request->block;
                target_node = entry->req_node_in_transient;
                // now that the original in M has gone to S:
                entry->presence[request->srcID] = false;
                entry->active_sharers--;
                // Directory serves as $-$ transfer agent:
                sim->cache_to_cache_transfers++;
                // Memory is updated since the original agent left the M state
                sim->memory_writes++;
                debug_printf("\t\t\tCache to cache transfer via directory: ");
                send_Request(target_node, tag_to_send, DATA);
                entry->state = M;
                entry->presence[target_node] = true;
                entry->active_sharers++;
                dequeue();
            }
            else if (entry->state == MS && request->msg == DATA)
            {
                // TODO: Fill me in

                // Current state is MS and the message is DATA. This means that the data can be sent to the agent that
                // requested the data and the block state can move to S.
                // do not need to modify presence for node that was in M since it is now in S
                // Directory serves as $-$ transfer agent:
                // Memory is updated since the original agent left the M state
                // debug_printf("\t\t\tCache to cache transfer via directory: ");
                // Set the state of the block to S since read only copies in agent caches
                // Remove request from the head of the request queue
                tag_to_send = request->block;
                target_node = entry->req_node_in_transient;
                sim->cache_to_cache_transfers++;
                debug_printf("\t\t\tCache to cache transfer via directory: ");
                send_Request(target_node, tag_to_send, DATA);
                entry->state = S;
                sim->memory_writes++;
                entry->presence[target_node] = true;
                entry->active_sharers++;
                dequeue();
            }
            else if (entry->state == S && request->msg == GETM)
            {
                // TODO: Fill me in
                // Current state is S and the message is GETM. This means 1 of 3 events can happen:
                // - only the requester has the data and we upgrade it via ACK
                // - many (including the requester) have the data and we invalidate others then upgrade requester via ACK
                // - many (excluding requester) have the data and we invalidate others then go to mem to get the data
                // Send invalidation messages to nodes that have the data and are not the requester
                // debug_printf("\t\t\tSending Invalidate to %lu: ", <var>);

                // if no invalidate messages were sent, this means that the requester was in S and no other nodes had presence
                // This means we can ACK the requester and move on to M

                // if any invalidate messages were sent, we must got to SM and wait for them to be INVACK before we can do anything more

                // debug_printf("\t\t\tRequester is already in S and is only sharer, upgrade: ");

                // Remove request from the head of the request queue
                // dequeue();
                entry->inv_ack_waiting = 0;
                for (nodeID_t i = 0; i < settings.num_procs; i++)
                {
                    if (entry->presence[i])
                    {
                        if (i != request->srcID)
                        {
                            // invalidate the others
                            tag_to_send = request->block;
                            target_node = i;
                            entry->inv_ack_waiting++;
                            debug_printf("\t\t\tSending Invalidate to %lu: ", i);
                            send_Request(i, tag_to_send, REQ_INVALID);
                        }
                        else
                        {
                            // once all invalidates have been ack'd only the orig requester can have presence
                        }
                    }
                }
                if (entry->inv_ack_waiting == 0)
                {
                    debug_printf("\t\t\tRequester is already in S and is only sharer, upgrade: ");
                    tag_to_send = request->block;
                    target_node = request->srcID;
                    send_Request(target_node, tag_to_send, ACK);
                    entry->state = M;
                }
                else
                {
                    entry->state = SM;
                    entry->req_node_in_transient = request->srcID;
                }

                // }
                dequeue();
            }
            else if (entry->state == S && request->msg == GETS)
            {
                // TODO: Fill me in

                // S is not a $-$ transfer agent so have to get from mem (similar to I state when seeing a GETS)

                // debug_printf("\t\t\tRequesting data from memory\n");
                request_in_progress = true;
                tag_to_send = request->block;
                target_node = request->srcID;
                response_time = Global_Clock + mem_latency;
                entry->state = S;
                entry->presence[request->srcID] = true;
                entry->active_sharers++;
                debug_printf("\t\t\tRequesting data from memory\n");
                // Remove request from the head of the request queue
                dequeue();
            }
            else if ((entry->state == SM) && (request->msg == INVACK))
            {
                // TODO: Fill me in

                // Transitioning from S to M, and waiting on invalid ACKs from all agent's who were sent the invalidate
                // message. Wait until all invalid acks have been received.

                // Decrement entry inv_ack_waiting until we get to the last invalidate:

                // debug_printf("\t\t\tMarking node %lu as invalid, %d acks remaining\n", <var>, <var>);
                // Once all invalid acks have been received, One of 2 cases can occur:
                // - only the requester has the data and we upgrade it via ACK
                // - the requester does not have the data and we must go to memory

                // debug_printf("\t\t\tFinal invack received, upgrading requester to M: ");
                // debug_printf("\t\t\tFinal invack received, fetching data from memory\n");
                if (entry->inv_ack_waiting >= 1)
                {
                    entry->presence[request->srcID] = false;
                    entry->inv_ack_waiting--;
                    entry->active_sharers--;
                    debug_printf("\t\t\tMarking node %lu as invalid, %d acks remaining\n", request->srcID,
                                 entry->inv_ack_waiting);
                }
                else
                {
                    fatal_error("\t\t\tReceived too many invacks\n");
                }
                if (entry->inv_ack_waiting == 0)
                {
                    if (entry->presence[entry->req_node_in_transient])
                    {
                        tag_to_send = request->block;
                        target_node = entry->req_node_in_transient;
                        debug_printf("\t\t\tFinal invack received, upgrading requester to M: ");
                        send_Request(target_node, tag_to_send, ACK);
                        entry->state = M;
                    }
                    else
                    {
                        request_in_progress = true;
                        tag_to_send = request->block;
                        target_node = entry->req_node_in_transient;
                        response_time = Global_Clock + mem_latency;
                        entry->presence[entry->req_node_in_transient] = true;
                        entry->active_sharers++;
                        debug_printf("\t\t\tFinal invack received, fetching data from memory\n");
                        entry->state = M;
                    }
                }
                dequeue();
                // Remove request from the head of the request queue;
            }
            else if ((entry->state == SM || entry->state == MM || entry->state == MS) &&
                     (request->msg == GETM || request->msg == GETS))
            {
                // When in a transition state if the request type is not DATA or INVACK, just push the request to the
                // back of the queue (cycling)
                debug_printf("\t\t\tCycling queue\n");
                cycle_queue();
            }
            else
            {
                fatal_error("\t\t\tInvalid state in directory for this request\n");
            }

            print_presence(entry);
        }
    }

    if (request_in_progress && Global_Clock >= response_time)
    {
        // Requisite time for Memory Access has passed:
        sim->memory_reads++;
        debug_printf("\t\t\tsending data from memory: ");
        send_Request(target_node, tag_to_send, DATA);
        request_in_progress = false;
    }
}
