<h1>Flux OS</h1>
This operating system is built for x86_64 and for (possibly) slower systems<br>
It has its own kernel and uses limine as its protocol and bootloader<br>

Screenshot 2-4-26 by JM-Pilot (FluxOS V 0.1.0)
![image info](./extra/sc/Screenshot1.png)

<h2>Goals</h2>
Have a shell<br>Have a working TSS<br>Have a working Userspace<br>

<h2>Compilation</h2>
Must have before compiling:<br>

```
xorriso (iso making)
gcc (elf-x86_64)
binutils (elf-x86_64)
git (for limine cloning)
qemu (for running)
```

Clean before compiling:<br>
```
make clean  
```

Make and Run<br>
```
make run
```