# Ceph RBD (RADOS Block Device)

Một block là một chuỗi các byte (thường là 512). Giao diện block storage phù hợp và phổ biến để lưu trữ dữ liệu trên các thiết bị bao gồm HDD, SSD, CD,...
Sự phổ biến của các giao diện block device là kết hợp hoàn hảo những cụm lưu trữ dữ liệu lớn bao gồm Ceph.

Ceph block device hỗ trợ thin-provisioned, resizable, và phân bổ dữ liệu trên các OSD.
Các Ceph block device cũng thừa hưởng các tính năng của RADOS bao gồm snapshot, replicate và tính nhất quán mạnh mẽ.

Tương tự như một một ổ đĩa ảo với khả năng mapped, formated và mounted. Dữ liệu khi được lưu trữ trong RADOS sẽ được RBD bổ ra thành nhiều block và phân tán ra khắp cluster (pool). Và khi muốn truy cập và sử dụng chúng sẽ cần thông qua librbd. Ngoài ra cũng có thể map RBD image như một device trong Linux, vì RBD driver được tích hợp với Linux kenel.

![image](https://user-images.githubusercontent.com/83684068/128803923-450528df-6cf7-4f60-8b10-32be23d1e300.png)

Các block device của Ceph mang lại hiệu suất và khả năng mở rộng cao tới các kernel module hay KVM như QEMU và các hệ thống điện toán đám mây như OpenStack và CloudStack dựa trên libvirt và QEMU để tích hợp với các thiết bị khối Ceph.
Cũng có thể sử dụng cùng một cluster để vận hành đồng thời cả Ceph RADOS Gateway, Ceph File System và các Ceph block device.
