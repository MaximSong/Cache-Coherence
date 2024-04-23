# Experiment of Performance
## 1. Array Sum
### (a) Array Block
#### MSI protocols
Type the following command in the terminal:\
``./dirsim -p MSI -t ./experiments/traces/array_block/core_8/ -n 8``\
Result:

    Selected Configuration:
        Protocol: MSI_PRO
        Trace Directory: ./experiments/traces/array_block/core_8/
        Num Procs: 8
        CPU TYPE: FICI_CPU
        Network Topology: RING_TOP
        Link Width: 8 bytes
        Memory Latency: 100
        Block Size: 6
    Starting simulation
    Simulation complete
    Cycles: 6340
    Cache Misses:           65 misses
    Cache Accesses:       2736 accesses
    Silent Upgrades:         0 upgrades
    $-to-$ Transfers:        7 transfers
    Memory Reads:           58 reads
    Memory Writes:           7 writes
It takes 6340 cycles to finish.
#### MESI protocols
Type the following command in the terminal:\
``./dirsim -p MESI -t ./experiments/traces/array_block/core_8/ -n 8``\
Result:

    Selected Configuration:
            Protocol: MESI_PRO
            Trace Directory: ./experiments/traces/array_block/core_8/
            Num Procs: 8
            CPU TYPE: FICI_CPU
            Network Topology: RING_TOP
            Link Width: 8 bytes
            Memory Latency: 100
            Block Size: 6
    Starting simulation
    Simulation complete
    Cycles: 5493
    Cache Misses:           65 misses
    Cache Accesses:       2736 accesses
    Silent Upgrades:         0 upgrades
    $-to-$ Transfers:       17 transfers
    Memory Reads:           48 reads
    Memory Writes:           7 writes
It takes 5493 cycles to finish.
#### MOSI protocols
Type the following command in the terminal:\
``./dirsim -p MOSI -t ./experiments/traces/array_block/core_8/ -n 8``\
Result:

    Selected Configuration:
            Protocol: MOSI_PRO
            Trace Directory: ./experiments/traces/array_block/core_8/
            Num Procs: 8
            CPU TYPE: FICI_CPU
            Network Topology: RING_TOP
            Link Width: 8 bytes
            Memory Latency: 100
            Block Size: 6
    Starting simulation
    Simulation complete
    Cycles: 6340
    Cache Misses:           65 misses
    Cache Accesses:       2736 accesses
    Silent Upgrades:         0 upgrades
    $-to-$ Transfers:        7 transfers
    Memory Reads:           58 reads
    Memory Writes:           7 writes
It takes 6340 cycles to finish.
#### MOESIF protocols
Type the following command in the terminal:\
``./dirsim -p MOESIF -t ./experiments/traces/array_block/core_8/ -n 8``\
Results:

    Selected Configuration:
            Protocol: MOESIF_PRO
            Trace Directory: ./experiments/traces/array_block/core_8/
            Num Procs: 8
            CPU TYPE: FICI_CPU
            Network Topology: RING_TOP
            Link Width: 8 bytes
            Memory Latency: 100
            Block Size: 6
    Starting simulation
    Simulation complete
    Cycles: 4516
    Cache Misses:           65 misses
    Cache Accesses:       2736 accesses
    Silent Upgrades:         0 upgrades
    $-to-$ Transfers:       29 transfers
    Memory Reads:           36 reads
    Memory Writes:           7 writes
It takes 4516 cycles to finish.
#### Analysis for Array Block

The `array_block_pthread.c` program splits an array into sections, each processed by different threads to compute sums concurrently.\

In testing, the `MOESIF protocol` demonstrated completed the task in 4516 cycles, compared to 5493 cycles under MESI and 6340 cycles for both MSI and MOSI. \

This superior performance of MOESIF can be attributed to its utilization of Owned (O) and Forward (F) states, which are particularly effective in a multi-threaded environment like this program. These states facilitate direct cache-to-cache data transfers, reducing the need for more costly memory reads.\

To be more specific, MOESIF's reduction of memory reads to 36, compared to 48 in MESI, and it's \$-to-$ Transfers are higher than the other protocols, optimizing the parallel computation of the sum and significantly speeding up the process.
### (b) Array Stripe
#### MSI protocols
Type the following command in the terminal:\
``./dirsim -p MSI -t ./experiments/traces/array_stripe/core_8/ -n 8``\
Result:

    Selected Configuration:
            Protocol: MSI_PRO
            Trace Directory: ./experiments/traces/array_stripe/core_8/
            Num Procs: 8
            CPU TYPE: FICI_CPU
            Network Topology: RING_TOP
            Link Width: 8 bytes
            Memory Latency: 100
            Block Size: 6
    Starting simulation
    Simulation complete
    Cycles: 28751
    Cache Misses:          287 misses
    Cache Accesses:       2760 accesses
    Silent Upgrades:         0 upgrades
    $-to-$ Transfers:        7 transfers
    Memory Reads:          280 reads
    Memory Writes:           7 writes
It takes 28751 cycles to finish.
#### MESI protocols
Type the following command in the terminal:\
``./dirsim -p MESI -t ./experiments/traces/array_stripe/core_8/ -n 8``\
Result:

    Selected Configuration:
            Protocol: MESI_PRO
            Trace Directory: ./experiments/traces/array_stripe/core_8/
            Num Procs: 8
            CPU TYPE: FICI_CPU
            Network Topology: RING_TOP
            Link Width: 8 bytes
            Memory Latency: 100
            Block Size: 6
    Starting simulation
    Simulation complete
    Cycles: 26196
    Cache Misses:          287 misses
    Cache Accesses:       2760 accesses
    Silent Upgrades:         0 upgrades
    $-to-$ Transfers:       42 transfers
    Memory Reads:          245 reads
    Memory Writes:           7 writes
It takes 26196 cycles to finish.
#### MOSI protocols
Type the following command in the terminal:\
``./dirsim -p MOSI -t ./experiments/traces/array_stripe/core_8/ -n 8``\
Result:

    Selected Configuration:
            Protocol: MOSI_PRO
            Trace Directory: ./experiments/traces/array_stripe/core_8/
            Num Procs: 8
            CPU TYPE: FICI_CPU
            Network Topology: RING_TOP
            Link Width: 8 bytes
            Memory Latency: 100
            Block Size: 6
    Starting simulation
    Simulation complete
    Cycles: 28751
    Cache Misses:          287 misses
    Cache Accesses:       2760 accesses
    Silent Upgrades:         0 upgrades
    $-to-$ Transfers:        7 transfers
    Memory Reads:          280 reads
    Memory Writes:           7 writes
It takes 28751 cycles to finish.
#### MOESIF protocols
Type the following command in the terminal:\
``./dirsim -p MOESIF -t ./experiments/traces/array_stripe/core_8/ -n 8``\
Result:

    Selected Configuration:
            Protocol: MOESIF_PRO
            Trace Directory: ./experiments/traces/array_stripe/core_8/
            Num Procs: 8
            CPU TYPE: FICI_CPU
            Network Topology: RING_TOP
            Link Width: 8 bytes
            Memory Latency: 100
            Block Size: 6
    Starting simulation
    Simulation complete
    Cycles: 6680
    Cache Misses:          287 misses
    Cache Accesses:       2760 accesses
    Silent Upgrades:         0 upgrades
    $-to-$ Transfers:      251 transfers
    Memory Reads:           36 reads
    Memory Writes:           7 writes
It takes 6680 cycles to finish.
#### Analysis for Array Stripe
In the array_stripe benchmark, where threads access the array in an interleaved pattern, the MOESIF protocol vastly outperforms others, completing the task in just 6680 cycles compared to over 26000 cycles by MESI and even more by MSI and MOSI.

This efficiency stems from MOESIF’s advanced cache state management, particularly its Owned (O) and Forward (F) states, which facilitate direct cache-to-cache data transfers and significantly reduce the need for slower main memory accesses. The protocol's ability to efficiently handle frequent cache misses and synchronize data among multiple cores with high cache-to-cache transfers (251 transfers) and minimal memory reads (36 reads) makes it exceptionally suited for applications with complex memory access patterns like the array_stripe setup.
### Analysis for Array Sum Benchmark

In the `array_block` benchmark, performance benefits stem from the contiguous memory access pattern of each thread. Each thread processes a sequential segment of the array, which improves cache locality and minimizes cache misses. Since each segment is handled independently by a different thread, there's less need for inter-thread communication and cache synchronization, resulting in more efficient use of the cache and faster computation times.

Conversely, the `array_stripe` benchmark involves threads accessing the array in an interleaved pattern, where each thread picks elements spread out across the entire array at regular intervals. This pattern significantly increases cache misses due to the non-contiguous nature of data access. Additionally, it requires more frequent synchronization among caches to maintain coherence, as threads are more likely to need access to overlapping parts of the array stored in different caches. This leads to increased cache coherence traffic and reduced overall performance compared to the  `array_block` setup.
## 2. Matrix Multiply
### (a) MatMul Rows
#### MSI protocols
Type the following command in the terminal:\
``./dirsim -p MSI -t ./experiments/traces/matmul_row/core_8/ -n 8``\
Result:

    Selected Configuration:
            Protocol: MSI_PRO
            Trace Directory: ./experiments/traces/matmul_row/core_8/
            Num Procs: 8
            CPU TYPE: FICI_CPU
            Network Topology: RING_TOP
            Link Width: 8 bytes
            Memory Latency: 100
            Block Size: 6
    Starting simulation
    Simulation complete
    Cycles: 59906
    Cache Misses:          810 misses
    Cache Accesses:      92400 accesses
    Silent Upgrades:         0 upgrades
    $-to-$ Transfers:      553 transfers
    Memory Reads:          265 reads
    Memory Writes:         553 writes
It takes 59906 cycles to finish.
#### MESI protocols
Type the following command in the terminal:\
``./dirsim -p MESI -t ./experiments/traces/matmul_row/core_8/ -n 8``\
Result:

    Selected Configuration:
            Protocol: MESI_PRO
            Trace Directory: ./experiments/traces/matmul_row/core_8/
            Num Procs: 8
            CPU TYPE: FICI_CPU
            Network Topology: RING_TOP
            Link Width: 8 bytes
            Memory Latency: 100
            Block Size: 6
    Starting simulation
    Simulation complete
    Cycles: 58977
    Cache Misses:          790 misses
    Cache Accesses:      92400 accesses
    Silent Upgrades:        65 upgrades
    $-to-$ Transfers:      574 transfers
    Memory Reads:          230 reads
    Memory Writes:         540 writes
It takes 58977 cycles to finish.

#### MOSI protocols
Type the following command in the terminal:\
``./dirsim -p MOSI -t ./experiments/traces/matmul_row/core_8/ -n 8``\
Result:

    Selected Configuration:
            Protocol: MOSI_PRO
            Trace Directory: ./experiments/traces/matmul_row/core_8/
            Num Procs: 8
            CPU TYPE: FICI_CPU
            Network Topology: RING_TOP
            Link Width: 8 bytes
            Memory Latency: 100
            Block Size: 6
    Starting simulation
    Simulation complete
    Cycles: 62913
    Cache Misses:          724 misses
    Cache Accesses:      92400 accesses
    Silent Upgrades:         0 upgrades
    $-to-$ Transfers:      606 transfers
    Memory Reads:          264 reads
    Memory Writes:         327 writes
It takes 62913 cycles to finish.
#### MOESIF protocols
Type the following command in the terminal:\
``./dirsim -p MOESIF -t ./experiments/traces/matmul_row/core_8/ -n 8``\
Result:

    Selected Configuration:
            Protocol: MOESIF_PRO
            Trace Directory: ./experiments/traces/matmul_row/core_8/
            Num Procs: 8
            CPU TYPE: FICI_CPU
            Network Topology: RING_TOP
            Link Width: 8 bytes
            Memory Latency: 100
            Block Size: 6
    Starting simulation
    Simulation complete
    Cycles: 54322
    Cache Misses:          848 misses
    Cache Accesses:      92400 accesses
    Silent Upgrades:        65 upgrades
    $-to-$ Transfers:      759 transfers
    Memory Reads:          101 reads
    Memory Writes:         420 writes
It takes 54322 cycles to finish.
#### Analysis for MatMul Rows

In the MatMul Rows benchmark, the `MOESIF` protocol significantly outperformed others, completing the matrix multiplication task in just 54322 cycles, compared to higher cycles required by MSI, MESI, and MOSI protocols.

 This efficiency in MOESIF can be attributed to its advanced cache states like Owned (O) and Forward (F), which facilitate effective data sharing and minimize memory traffic. With the lowest number of memory reads (101 reads) and the highest cache-to-cache transfers (759 transfers), MOESIF enhances data availability and consistency across threads, reducing the need for frequent main memory accesses. This optimized cache coherence mechanism is crucial for operations like matrix multiplication, where rapid, synchronized access to shared data is essential for performance.
### (b) MatMul Cols
#### MSI protocols
Type the following command in the terminal:\
``./dirsim -p MSI -t ./experiments/traces/matmul_col/core_8/ -n 8``\
Results:

    Selected Configuration:
            Protocol: MSI_PRO
            Trace Directory: ./experiments/traces/matmul_col/core_8/
            Num Procs: 8
            CPU TYPE: FICI_CPU
            Network Topology: RING_TOP
            Link Width: 8 bytes
            Memory Latency: 100
            Block Size: 6
    Starting simulation
    Simulation complete
    Cycles: 227346
    Cache Misses:         3302 misses
    Cache Accesses:     118504 accesses
    Silent Upgrades:         0 upgrades
    $-to-$ Transfers:     2744 transfers
    Memory Reads:          999 reads
    Memory Writes:        2744 writes
It takes 227346 cycles to finish.
#### MESI protocols
Type the following command in the terminal:\
``./dirsim -p MESI -t ./experiments/traces/matmul_col/core_8/ -n 8``\
Results:

    Selected Configuration:
            Protocol: MESI_PRO
            Trace Directory: ./experiments/traces/matmul_col/core_8/
            Num Procs: 8
            CPU TYPE: FICI_CPU
            Network Topology: RING_TOP
            Link Width: 8 bytes
            Memory Latency: 100
            Block Size: 6
    Starting simulation
    Simulation complete
    Cycles: 195788
    Cache Misses:         2800 misses
    Cache Accesses:     118504 accesses
    Silent Upgrades:        63 upgrades
    $-to-$ Transfers:     2358 transfers
    Memory Reads:          751 reads
    Memory Writes:        2320 writes
It takes 195788 cycles to finish.
#### MOSI protocols
Type the following command in the terminal:\
``./dirsim -p MOSI -t ./experiments/traces/matmul_col/core_8/ -n 8``\
Results:

    Selected Configuration:
            Protocol: MOSI_PRO
            Trace Directory: ./experiments/traces/matmul_col/core_8/
            Num Procs: 8
            CPU TYPE: FICI_CPU
            Network Topology: RING_TOP
            Link Width: 8 bytes
            Memory Latency: 100
            Block Size: 6
    Starting simulation
    Simulation complete
    Cycles: 170598
    Cache Misses:         2565 misses
    Cache Accesses:     118504 accesses
    Silent Upgrades:         0 upgrades
    $-to-$ Transfers:     3505 transfers
    Memory Reads:          359 reads
    Memory Writes:        1824 writes
It takes 170598 cycles to finish.
#### MOESIF protocols
Type the following command in the terminal:\
``./dirsim -p MOESIF -t ./experiments/traces/matmul_col/core_8/ -n 8``\
Results:

    Selected Configuration:
            Protocol: MOESIF_PRO
            Trace Directory: ./experiments/traces/matmul_col/core_8/
            Num Procs: 8
            CPU TYPE: FICI_CPU
            Network Topology: RING_TOP
            Link Width: 8 bytes
            Memory Latency: 100
            Block Size: 6
    Starting simulation
    Simulation complete
    Cycles: 121722
    Cache Misses:         1974 misses
    Cache Accesses:     118504 accesses
    Silent Upgrades:        65 upgrades
    $-to-$ Transfers:     2062 transfers
    Memory Reads:          101 reads
    Memory Writes:        1338 writes
It takes 121722 cycles to finish.
#### Analysis for MatMul Cols
In the MatMul Cols benchmark, the `MOESIF protocol` outperforms MSI, MESI, and MOSI, completing the matrix multiplication in only 121722 cycles.

 This efficiency is largely due to MOESIF's advanced cache state management, specifically its Owned (O) and Forward (F) states, which optimize data sharing and reduce memory traffic. MOESIF reduces memory reads to just 101, compared to higher numbers in other protocols.
 
  This is particularly advantageous in scenarios like column-based matrix multiplication, where frequent, synchronized access to shared data across different processors is critical for performance.
### Analysis for Matrix Multiply Benchmark

In the "matmul rows" benchmark, each thread is assigned a specific set of contiguous rows from matrix a and is responsible for calculating the corresponding rows of the resultant matrix c. This arrangement tends to localize memory access within a specific range, promoting better cache utilization and minimizing cache misses. 

The localized access pattern means that once a row of matrix a is loaded into the cache, it can be used effectively to compute multiple elements of matrix c across all columns, reducing the need to frequently access the main memory. However, this can also mean increased cache-to-cache transfers when different threads need to access overlapping columns of matrix b, which is a shared resource among the threads.

Conversely, in the "matmul cols" benchmark, threads are assigned specific sets of columns from matrix b to work on, affecting all rows of the output matrix c. This distribution leads to a less localized but more distributed memory access pattern, as each thread has to access entire rows of matrix a to compute partial results for columns of matrix c. This widespread access increases cache misses since data from matrix a cannot stay in the cache long enough before being evicted due to the needs from other threads working on different columns.**The interleaving of memory accesses across all rows and the continuous requirement for different parts of matrix a result in higher memory traffic and potential contention points in the memory system.**
## 3.Pipeline
#### MSI protocols
Type the following command in the terminal:\
``./dirsim -p MSI -t ./experiments/traces/pipeline/core_8/ -n 8``\
Results:

    Selected Configuration:
            Protocol: MSI_PRO
            Trace Directory: ./experiments/traces/pipeline/core_8/
            Num Procs: 8
            CPU TYPE: FICI_CPU
            Network Topology: RING_TOP
            Link Width: 8 bytes
            Memory Latency: 100
            Block Size: 6
    Starting simulation
    Simulation complete
    Cycles: 108778
    Cache Misses:          836 misses
    Cache Accesses:       9483 accesses
    Silent Upgrades:         0 upgrades
    $-to-$ Transfers:      828 transfers
    Memory Reads:          567 reads
    Memory Writes:         828 writes
It takes 108778 cycles to finish.
#### MESI protocols
Type the following command in the terminal:\
``./dirsim -p MESI -t ./experiments/traces/pipeline/core_8/ -n 8``\
Results:

    Selected Configuration:
            Protocol: MESI_PRO
            Trace Directory: ./experiments/traces/pipeline/core_8/
            Num Procs: 8
            CPU TYPE: FICI_CPU
            Network Topology: RING_TOP
            Link Width: 8 bytes
            Memory Latency: 100
            Block Size: 6
    Starting simulation
    Simulation complete
    Cycles: 107552
    Cache Misses:          828 misses
    Cache Accesses:       9483 accesses
    Silent Upgrades:         7 upgrades
    $-to-$ Transfers:      827 transfers
    Memory Reads:          556 reads
    Memory Writes:         813 writes
It takes 107552 cycles to finish.
#### MOSI protocols
Type the following command in the terminal:\
``./dirsim -p MOSI -t ./experiments/traces/pipeline/core_8/ -n 8``\
Results:

    Selected Configuration:
            Protocol: MOSI_PRO
            Trace Directory: ./experiments/traces/pipeline/core_8/
            Num Procs: 8
            CPU TYPE: FICI_CPU
            Network Topology: RING_TOP
            Link Width: 8 bytes
            Memory Latency: 100
            Block Size: 6
    Starting simulation
    Simulation complete
    Cycles: 84559
    Cache Misses:          818 misses
    Cache Accesses:       9483 accesses
    Silent Upgrades:         0 upgrades
    $-to-$ Transfers:     1378 transfers
    Memory Reads:          135 reads
    Memory Writes:         726 writes
It takes 84559 cycles to finish.
#### MOESIF protocols
Type the following command in the terminal:\
``./dirsim -p MOESIF -t ./experiments/traces/pipeline/core_8/ -n 8``\
Results:

    Selected Configuration:
            Protocol: MOESIF_PRO
            Trace Directory: ./experiments/traces/pipeline/core_8/
            Num Procs: 8
            CPU TYPE: FICI_CPU
            Network Topology: RING_TOP
            Link Width: 8 bytes
            Memory Latency: 100
            Block Size: 6
    Starting simulation
    Simulation complete
    Cycles: 80351
    Cache Misses:          846 misses
    Cache Accesses:       9483 accesses
    Silent Upgrades:         7 upgrades
    $-to-$ Transfers:     1343 transfers
    Memory Reads:           54 reads
    Memory Writes:         772 writes
It takes 80351 cycles to finish.
#### Analysis for Pipeline

In the Pipeline benchmark, the MOESIF protocol demonstrated superior performance, completing the task in 80351 cycles, markedly less than the 108778 cycles taken by the MSI protocol, the 107552 cycles by the MESI protocol, and the 84559 cycles by the MOSI protocol.

This significant reduction in cycle count under MOESIF can be attributed to its efficient cache state management, which minimized memory reads to just 54 and facilitated 1343 cache-to-cache transfers. The effective reduction in memory operations and enhancement of cache-to-cache communications underscores MOESIF's suitability for scenarios demanding rapid and efficient data processing across multiple computational stages.
## 4. Map-Reduce
#### MSI protocols
Type the following command in the terminal:\
``./dirsim -p MSI -t ./experiments/traces/mapreduce/core_8/ -n 8``\
Results:

    Selected Configuration:
            Protocol: MSI_PRO
            Trace Directory: ./experiments/traces/mapreduce/core_8/
            Num Procs: 8
            CPU TYPE: FICI_CPU
            Network Topology: RING_TOP
            Link Width: 8 bytes
            Memory Latency: 100
            Block Size: 6
    Starting simulation
    Simulation complete
    Cycles: 73327
    Cache Misses:          637 misses
    Cache Accesses:      11281 accesses
    Silent Upgrades:         0 upgrades
    $-to-$ Transfers:      570 transfers
    Memory Reads:          424 reads
    Memory Writes:         570 writes
It takes 73327 cycles to finish.
#### MESI protocols
Type the following command in the terminal:\
``./dirsim -p MESI -t ./experiments/traces/mapreduce/core_8/ -n 8``\
Results:

    Selected Configuration:
            Protocol: MESI_PRO
            Trace Directory: ./experiments/traces/mapreduce/core_8/
            Num Procs: 8
            CPU TYPE: FICI_CPU
            Network Topology: RING_TOP
            Link Width: 8 bytes
            Memory Latency: 100
            Block Size: 6
    Starting simulation
    Simulation complete
    Cycles: 72421
    Cache Misses:          636 misses
    Cache Accesses:      11281 accesses
    Silent Upgrades:        10 upgrades
    $-to-$ Transfers:      579 transfers
    Memory Reads:          414 reads
    Memory Writes:         562 writes
It takes 72421 cycles to finish.
#### MOSI protocols
Type the following command in the terminal:\
``./dirsim -p MOSI -t ./experiments/traces/mapreduce/core_8/ -n 8``\
Results:

    Selected Configuration:
            Protocol: MOSI_PRO
            Trace Directory: ./experiments/traces/mapreduce/core_8/
            Num Procs: 8
            CPU TYPE: FICI_CPU
            Network Topology: RING_TOP
            Link Width: 8 bytes
            Memory Latency: 100
            Block Size: 6
    Starting simulation
    Simulation complete
    Cycles: 61319
    Cache Misses:          620 misses
    Cache Accesses:      11281 accesses
    Silent Upgrades:         0 upgrades
    $-to-$ Transfers:      879 transfers
    Memory Reads:          151 reads
    Memory Writes:         462 writes
It takes 61319 cycles to finish.
#### MOESIF protocols
Type the following command in the terminal:\
``./dirsim -p MOESIF -t ./experiments/traces/mapreduce/core_8/ -n 8``\
Results:

    Selected Configuration:
            Protocol: MOESIF_PRO
            Trace Directory: ./experiments/traces/mapreduce/core_8/
            Num Procs: 8
            CPU TYPE: FICI_CPU
            Network Topology: RING_TOP
            Link Width: 8 bytes
            Memory Latency: 100
            Block Size: 6
    Starting simulation
    Simulation complete
    Cycles: 53324
    Cache Misses:          679 misses
    Cache Accesses:      11281 accesses
    Silent Upgrades:        12 upgrades
    $-to-$ Transfers:      986 transfers
    Memory Reads:           52 reads
    Memory Writes:         512 writes
It takes 53324 cycles to finish.
#### Analysis for Map-Reduce
 The MOESIF protocol performs exceptionally well, completing the task in 53,324 cycles, significantly faster than MSI at 73,327 cycles, MESI at 72,421 cycles, and MOSI at 61,319 cycles. 
 
 This enhanced performance in MOESIF is attributed to its efficient handling of cache states which minimizes memory reads to just 52, compared to higher numbers in other protocols. MOESIF's ability to effectively manage cache-to-cache transfers, totaling 986, optimizes data sharing between cores, essential for the Map-Reduce operations where data must be frequently shuffled between the map and reduce phases. These characteristics make MOESIF particularly suited for the concurrent and distributed nature of Map-Reduce tasks, ensuring faster data processing and reduced latency across multiple cores.