## Trạng thái bảo trì
Một hệ thống trên thực tế sẽ cần thực hiện bảo trì, nâng cấp và sửa lỗi, giải quyết sự cố trong failure domain.
Các mức độ bảo trì có thể trên một osd, một rack, hay toàn bộ cluster.

Tuy nhiên không thể ngắt bỏ hay thay thế ngay lập tức một OSD hay một host được, vì cluster đang trong quá trình hoạt động và client thì đang ghi dữ liệu.
Trước khi thực hiện các hành động bảo trì, cần tắt tính năng tự động cân bằng của CRUSH bằng flag `noout`, ví dụ đối với một OSD cụ thể:

    ceph osd add-noout osd.0
    ceph osd rm-noout  osd.0
    
Hay ví dụ cần add thêm RAM ở một bucket tên `ceph-data1701`:

    ceph osd set-group noout ceph-data1701
    ceph osd unset-group noout ceph-data1701

Hoặc có thể là toàn bộ cluster:

    ceph osd set noout
    ceph osd unset noout
    
Sau khi flag đã được set hoàn tất, có thể dừng các OSD hoặc các service khác trong failure domain để tiến hành bảo trì.

    systemctl stop ceph-@...
    
##     

