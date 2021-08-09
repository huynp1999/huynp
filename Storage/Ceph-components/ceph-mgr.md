# Ceph Manager
Ceph Manager (ceph-mgr) chạy song song cùng với hệ thống và làm nền giám sát chính, nhằm cung cấp hệ thống giám sát và giao diện bổ sung cho các hệ thống quản lý và giám sát bên ngoài.
Kể từ khi phát hành Ceph 12.x (Luminous), dịch vụ ceph-mgr được yêu cầu cài đặt luôn sau khi cài hệ thống và là một service cần thiết cho các hoạt động của Ceph cluster.

Theo mặc định, ceph-mgr không yêu cầu cấu hình bổ sung nhưng cần đảm bảo service mgr phải được hoạt động. Nếu không có service mgr nào đang chạy, sẽ có cảnh báo về HEALTH cho cụm Ceph.

Ceph-mgr cung cấp các module bổ sung như Dashboard, ResfullAPI, Zabbix, Prometheus chủ yếu tập trung vào việc thu thập số liệu trên toàn cluster, cũng như hỗ trợ thao tác với cụm Ceph trên Dashboard (từ bản Nautilus 14.2.x)

Ceph-mgr thường được triển khai trên một node MON dựa vào các công cụ deploy như cephadm, ceph-ansible, ceph-deploy,...

## High availability
Ceph-mgr nên được thiết lập trên mỗi server chạy daemon ceph-mon để đạt được cùng một mức độ khả dụng.
Theo mặc định, ceph-mgr nào triển khai trước sẽ được đặt `active` bởi MON và còn lại là `standby`.

Nếu daemon active không gửi được chỉ thị tới MON trong một khoảng thời gian `mon_mgr_beacon_grace`, thì nó sẽ được thay thế bởi một standby.
Nếu muốn xóa thủ công, có thể đánh fail daemon ceph-mgr đó bằng cách sử dụng `ceph mgr fail <mgr name>.`

## Sử dụng các module
Sử dụng lệnh `ceph mgr module ls` để xem module nào khả dụng và module nào hiện đang được bật. Bật hoặc tắt chúng bằng các câu lệnh `ceph mgr enable <module>` và `ceph mgr disable <module>`.

Nếu một module được bật thì active ceph-mgr daemon sẽ tải và thực thi nó.
Trong trường hợp module cung cấp dịch vụ, chẳng hạn như máy chủ HTTP, module có thể cung cấp địa chỉ khi được bật lên.
Để xem địa chỉ của các module `ceph mgr services`

Ví dụ

    $ ceph mgr module ls
    {
            "enabled_modules": [
                    "restful",
                    "status"
            ],
            "disabled_modules": [
                    "dashboard"
            ]
    }

    $ ceph mgr module enable dashboard
    $ ceph mgr module ls
    {
            "enabled_modules": [
                    "restful",
                    "status",
                    "dashboard"
            ],
            "disabled_modules": [
            ]
    }

    $ceph mgr services
    {
            "dashboard": "http://ceph01:8443/",
    }
