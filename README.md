�Ӻ���� ���忡 ���α׷��� �ö󰡴� ��ƾ ���͵� (for ���Ի�)
"Hello world"

���� : https://balau82.wordpress.com/2010/02/28/hello-world-for-bare-metal-arm-using-qemu/

==
boot loader �ٿ�ε� �� ������
==
$ git clone git://github.com/virtualopensystems/u-boot-arndale.git
$ cd u-boot-arndale
$ ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- make arndale5250

== 
������ ����
==
$ arm-linux-gnueabihf-as -g startup.s -o startup.o
$ arm-linux-gnueabihf-gcc -c -g test.c -o test.o
$ arm-linux-gnueabihf-ld -T test.ld test.o startup.o -o test.elf
$ arm-linux-gnueabi-objcopy -O binary test.elf test.bin 

==
���� ����
==
sudo dd if=arndale-bl1.bin of=/dev/sdb bs=512 seek=1
sudo dd if=./u-boot-native/spl/smdk5250-spl.bin of=/dev/sdb bs=512 seek=17
sudo dd if=./u-boot-native/u-boot.bin of=/dev/sdb bs=512 seek=49
sudo dd if=test.bin of=/dev/sdb bs=512 seek=1105
sudo sync
sudo umount /dev/sdb*

==
u-boot ������ ��ɾ�, ����� �ö󰬴��� ���̳ʸ� Ȯ���غ���
==
mmc read 0xa0000000 451 100;
go 0xa0000000
