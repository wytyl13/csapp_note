/**********************************************************************
 * Copyright (C) 2023. IEucd Inc. All rights reserved.
 * @Author: weiyutao
 * @Date: 2023-01-03 15:03:59
 * @Last Modified by: weiyutao
 * @Last Modified time: 2023-01-03 15:03:59
 * @Description: memory system is a hierarchy structure of the storage devices
 * with different capacity, cost and access time. the cache memory that close to CPU
 * is small and fast, it is the buffer zones for main memory that is slowly.
 * main memory is the operation memory, it stored the instruction and data. the main
 * memory is also the buffer zones for disk that big and slowly. the disk is also
 * the buffer zones for the other machine that connected use network. the memory system is feasible.
 * the effect it can achieve is the cost is equal to the hierarchical structure of the underlying storage device.
 * but it used the high speed that closed to the top of the hierarchy structure to provide data storage for program.
 * as a programmer, you should understand the storage hierarchy structure. you can get it will successful visit in 0 cycle if
 * you want to access data from register in your program. it will be 4~75 cycle if you want to access data from
 * cache memory, it will be hundreds of cycles if you want to access data from main memory. and it will be thousands of cycle
 * if you want to access data from disk. so you can improve the performance for your program by changing the position for hierarchy structure
 * that your data. so it is feasible for a qualified programmers. this idea we can named locality. it is also the attribute for computer system.
 * this meaning that the program with good locality tend to access data from a higher level in hierarchy structure. you can also understand it that
 * the program with good locality tend to access data from the same data items. so it will be more efficient than bad locality.
 * it means you will get the different time cost when you run the same program in the same computer, it is because the computer has 
 * the different locality.局部性不同造成程序的性能不同。
 * 
 * then, we will learn the storage technology.
 * Random-Access-Memory, it also can be named RAM. involver static and dynamic. the former SRAM is faster than DRAM.
 * SRAM is dedicated to the cache memory, the DRAM is dedicated to the main memory.
 * SRAM with a bistable. just like an inverted pendulum. it just has two stable status, to the left or right, it will be unstable
 * if the inverted pendulum is in the middle position. this feature make SRAM can store the data in the condition of electricity.
 * even if there is electricity interference, it will be return the original status if the interference is disappear.
 * but the DRAM just need to less of a transister, so it will be cheaper than SRAM, but the efficient will be even worse.
 * so it used to be used in main memory.
 *  __ __ __ __
 * |__|__|__|__|            
 * |__|__|__|__|            
 * |__|__|__|__|            
 * |__|__|__|__|                     
 * 
 * it is the super unit for DRAM, each DRAM chip has d=16 super unit, each super unit
 * has w=8 bits, each DRAM chip has 4 rows and 4 columns.
 * each DRAM chip has a memory controller, it can pass w=8 bits to DRAM chip or 
 * it involved incoming and outgoing. (0, 0)~(4, 4), you can operate used this method.
 * (RAS, CAS), the first param is Row Access Strobe, the second param is Column Access Strobe.
 * the DRAM will return the row data to buffer, then access the columnd data.
 * the disadvantages used this two dimensional array method is you must access data through two steps.
 * why do not use the linear array, you can understand it as 1 dimensional array.
 * because the linear array will cost 4 address pins.
 * DRAM chip encapsulated in memory module. the memory module in the motherboard.
 * 
 * volatitle, DRAM and SRAM will loss of informaation if power outages.
 * of course, nonvolatitle memory will still save the data if power outages.
 * this nonvolatitle memory innvolved Programmable ROM and Erasable Programable ROM,
 * the former can only be programmed once, the fuse for each memory unit in PROM
 * can only be fused one time by high current. the EPROM has a transparent quartz window.
 * allow the light reaches the storage unit, Ultraviolet can reset the storage unit.
 * EEPROM can reset 10^5 times. flash memory is a special EEPROM. it has been
 * a important storage technology. it is used in mobile phones, computer and so on.
 * the Solid State Disk, SSD is the newer application based on the flash memory. a special EEPROM电子可擦出PROM.
 * the program in ROM device is named firmware, when you open a computer, it will run the firmware
 * in ROM device, the firmware provide some I/O function for computer, just like BIOS, the basic I/O system.
 * 
 * and how to access the main memory?
 * bus, data flow can transmission from CPU to main memory used bus. these can be named
 * bus transaction, from main memory to CPU is named read transaction, from CPU to main memory
 * is named write transaction.
 * page440.
 * 
***********************************************************************/