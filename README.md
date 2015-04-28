임베디드 보드에 프로그램이 올라가는 루틴 스터디 (for 신입생)
"Hello world"

참조 : https://balau82.wordpress.com/2010/02/28/hello-world-for-bare-metal-arm-using-qemu/

==
boot loader 다운로드 및 컴파일
==
$ git clone git://github.com/virtualopensystems/u-boot-arndale.git
$ cd u-boot-arndale
$ ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- make arndale5250

== 
컴파일 예시
==
$ arm-linux-gnueabihf-as -g startup.s -o startup.o
$ arm-linux-gnueabihf-gcc -c -g test.c -o test.o
$ arm-linux-gnueabihf-ld -T test.ld test.o startup.o -o test.elf
$ arm-linux-gnueabi-objcopy -O binary test.elf test.bin 

==
보드 굽기
==
sudo dd if=arndale-bl1.bin of=/dev/sdb bs=512 seek=1
sudo dd if=./u-boot-native/spl/smdk5250-spl.bin of=/dev/sdb bs=512 seek=17
sudo dd if=./u-boot-native/u-boot.bin of=/dev/sdb bs=512 seek=49
sudo dd if=test.bin of=/dev/sdb bs=512 seek=1105
sudo sync
sudo umount /dev/sdb*

==
u-boot 에서의 명령어, 제대로 올라갔는지 바이너리 확인해보기
==
mmc read 0xa0000000 451 100;
go 0xa0000000
