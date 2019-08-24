<https://wiki.ubuntu.com/DebuggingProcedures>

### Info for the BugSquad

1. This will create a minimal Precise system:

   ```
   sudo mkdir -p /chroots/precise
   sudo debootstrap precise /chroots/precise/
   ```

2. Now change into this minimal precise system:

   ```
   sudo chroot /chroots/precise
   ```

3. Edit /etc/apt/sources/list and add all the repositories you need, including the ddeb repository.

4. Execute the following in a terminal:

   ```
   sudo apt-get update; sudo apt-get install gdb apport
   ```

5. use apport-retrace as you're used to.



### Compiling with debugging -g option

```shell
./autogen.sh
./configure CFLAGS="-g -O0" #option A
./configure --enable-debug  #option B
```

