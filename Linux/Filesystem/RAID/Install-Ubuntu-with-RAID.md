# Cài đặt Ubuntu 16.04 với RAID 1

Có sẵn hai drive là `vda` và `vdb`, thực hiện partition tương tự nhau:

![](https://github.com/huynp1999/huynp/blob/master/pic/linux/raid1.png)

Cấu hình 2 software RAID cho 2 phân vùng là `/` và swap:

![](https://github.com/huynp1999/huynp/blob/master/pic/linux/raid2.png)

Kết quả:

![](https://github.com/huynp1999/huynp/blob/master/pic/linux/raid3.png)

Kiểm tra:

    huynp@ubuntu:~$ cat /proc/mdstat
    Personalities : [raid1] [linear] [multipath] [raid0] [raid6] [raid5] [raid4] [raid10] 
    md0 : active raid1 vdb1[1] vda1[0]
          1950720 blocks super 1.2 [2/2] [UU]

    md1 : active raid1 vdb5[1] vda5[0]
          1189888 blocks super 1.2 [2/2] [UU]

    unused devices: <none>
    huynp@ubuntu:~$ lsblk
    NAME    MAJ:MIN RM  SIZE RO TYPE  MOUNTPOINT
    sr0      11:0    1 1024M  0 rom   
    vda     253:0    0    3G  0 disk  
    |-vda1  253:1    0  1.9G  0 part  
    | `-md0   9:0    0  1.9G  0 raid1 /
    |-vda2  253:2    0    1K  0 part  
    `-vda5  253:5    0  1.1G  0 part  
      `-md1   9:1    0  1.1G  0 raid1 [SWAP]
    vdb     253:16   0    3G  0 disk  
    |-vdb1  253:17   0  1.9G  0 part  
    | `-md0   9:0    0  1.9G  0 raid1 /
    |-vdb2  253:18   0    1K  0 part  
    `-vdb5  253:21   0  1.1G  0 part  
      `-md1   9:1    0  1.1G  0 raid1 [SWAP]
