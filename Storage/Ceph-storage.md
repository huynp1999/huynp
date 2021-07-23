# Ceph Storage
Ceph là phần mềm mã nguồn mở miễn phí, cung cấp giải pháp lưu trữ dữ liệu phân tán, ổn định, tin cậy và dễ dàng mở rộng trong tương lai.
Dữ liệu được hỗ trợ lưu trữ ở dạng đối tương (Object), khối (Block) hay tệp (File) trong cùng một nền tảng duy nhất.
Nền tảng storage này được xây dựng bằng phần mềm (software defined) và triển khai trên các máy chủ phổ thông.

Nguyên tắc cơ bản của Ceph:
- Khả năng mở rộng tất cả thành phần
- Tính chịu lỗi cao
- giải pháp dựa trên phần mềm mở, tính thích nghi cao
- Tương thích với mọi phần cứng

Ceph xây dựng kiến trúc mạnh mẽ, tính mở rộng cao, hiệu năng cao, nền tảng mạnh mẽ cho doanh nghiệp, giảm bớt sự phụ thuộc vào phần cứng đắt tiền.

Ceph universal storage system cung cấp khả năng lưu trữ trên block, file, object hoặc cho phép custom theo ý muốn. Trong đó object và block storage của Ceph thường thấy trong các nền tảng điện toán đám mây như OpenStack.

Nền tảng Ceph xây dựng dựa trên object, tổ chức blocks. Tất cả các kiểu dữ liệu, block, file đều được lưu trên object thuộc Ceph cluster. Object storage là giải pháp cho hệ thống lưu trữ truyền thống, cho phép xây dựng kiến trúc hạ tầng độc lập với phần cứng. Ceph quản lý và nhân bản (replicate) toàn cluster, nâng cao tính đảm bảo. Những object này sẽ không tồn tại đường dẫn vật lý, giúp việc lưu trữ được linh hoạt, tạo nền tảng mở rộng tới exabyte.

## Hệ thống lưu trữ thế hệ mới
Ceph storage system là giải pháp nổi bật cho vấn đề tăng trưởng dữ liệu toàn cầu. Với các đặc điểm nổi bật như tính thống nhất, phân phối, chí phí đầu tư, tiềm năng trong tương lai. Cộng đồng Linux đã nhìn thấy được tiềm năng này từ năm 2008 và đã tích hợp với Linux kernel, đặc điểm này khiến Ceph vượt trội hơn các giải pháp storage hiện tại.

![](https://raw.githubusercontent.com/lacoski/khoa-luan/master/Ceph/PIC/p1.png)

### Giải pháp cloud storage
Thành phần quan trọng để phát triển cloud chính là storage. Cloud cần storage để phát triển. Đồng thời, các giải pháp lưu trữ truyền thống đã dần tới giới hạn (chí phí, kiến trúc, tính mở rộng...). Ceph trở thành giải pháp để giải quyết vấn để đang gặp phải đáp ứng nhu cầu của cloud, hỗ trợ tốt các nền tảng cloud nổi bật như OpenStack, CloudStack, OpenNebula. Đội ngũ phát triển và hợp tác của Ceph bao gồm Canonical, Red Hat, SUSE, đều là những nhà cung cấp lớn, trau chuốt hoàn thiện Ceph, khiến sản phẩm luôn đi trước, bắt kịp thời đại, tương thích cao với Linux, thành 1 trong những hệ thống ưu tú để xây dựng storage backend.

### Giải pháp software-defined
Để tiết kiệm chi phí, Ceph cung cấp giải pháp dựa trên phần mềm Software-defined Storage (SDS). Dành cho những khách hàng đã có sẵn hạ tầng lớn, không mong muốn đâu tư thêm nhiều chi phí. SDS hỗ trợ tốt trên nhiều phấn cứng từ bất kỳ nhà cung cấp. Mang đến các lợi thế như low cost per GB, reliability, và scalability.

### Giải pháp lưu trữ thống nhất
Ceph mang đến giải pháp lưu trữ thống nhất bao gồm file-based và block-based access truy cập duy nhất qua 1 nền tảng. Đáp ứng tốt theo độ tăng trưởng dữ liệu hiện tại và cả trong tương lai. Giải pháp lưu trữ được thống nhất và đồng bộ qua lớp phần mềm, hỗ trợ lưu trữ các luồng dữ liệu lớn, khống có cấu trúc.

### Giải pháp thay thế metadata
Metadata là thông tin về dữ liệu, cho biết dữ liệu sẽ được viết và đọc tại đâu. Các hệ thống storage truyền thống cần 1 trung tâm quan lý, tìm kiếm thông tin về metadata. Khi mỗi client yêu cầu hoạt động read, write – storage sẽ tìm kiếm vị trí data trong 1 bảng metadata lớn. Với quy mổ nhỏ, độ trễ có thể là không đáng kể nhưng đối với hệ thống storage lớn thì độ trễ là rất cao, hạn chế sự mở rộng.

Object trong ceph được lưu trữ thông qua các định danh riêng biệt thay vì là những đường dẫn như truyền thống. Metadata giờ đây thay vì được lưu trữ và quản lý trong bảng, sẽ được quản lý bởi thuật toán động "CRUSH (Controlled Replication Under Scalable Hashing)". Thay vì tra cứu theo bảng metadata, thuật toán CRUSH sẽ dựa trên yêu cầu, tính toán vị trí data nên được ghi và đọc ở đâu, từ đó sẽ cải thiện tốc độ truy xuất chung. Hơn thế, thuật toán sẽ phân tán tới các cluster node, tận dụng sức mạnh lưu trữ phân tán. CRUSH quản lý metadata tốt hơn so với truyền thống.

Khi thành phần trong hệ thống xảy ra lỗi, CRUSH sẽ lưu trữ bản sao dữ liệu và nhân rộng chúng đến các phân vùng trong bộ nhớ, làm tăng tính sẵn sàng của dữ liệu. Đồng thời CRUSH cho phép Ceph tự quản trị và tự sửa lỗi và nhân rộng chúng trong cluster. Tại mọi thời điểm sẽ có hơn 1 bản sao lưu của data được phân tán trong cluster. Vì vậy, với CRUSH sẽ tạo ra hạ tầng lưu trữ đảm bảo, đáng tin cậy và Ceph nói chung sẽ tăng tính mở rộng, đảm bảo cho hệ thống lưu trữ.

## So sánh với RAID
Công nghệ RAID từng có những vị trí nhất định trong các hệ thống lưu trữ nhiều năm về trước. Tuy nhiên, RAID cũng đã đạt tới giới hạn, bắt đầu xuất hiện những điểm yếu rõ rệt khi ứng dụng trong những công nghệ mới. Công nghệ sản xuất ổ cứng ngày càng hiện đại với giá thành giảm dần, mà dung lượng dữ liệu lại tăng dần theo từng năm. Đối với khối lượng dữ liệu lớn, việc tái tạo dữ liệu bằng RAID càng tốn nhiều thời gian. Chỉ cần một ổ đĩa xảy ra lỗi cũng phải mất nhiều ngày giờ để khôi phục lại được, chưa kể đến trường hợp nhiều ổ đĩa cùng lỗi một lúc. Hơn hết Raid sử dụng nhiều tài nguyên, tăng TCO, và khi storage đến giới hạn, nó sẽ lại đẩy chi phí đầu tư lên. Đồng thời khi đầu tư RAID, cần phải quan tâm đến disk size, disk type, RPM là những yếu tố sẽ ảnh hưởng đến hiệu năng storage.

Việc sử dụng raid kéo theo thiết bị phần cứng đắt tiền – Raid card và có thể phát sinh lỗi khi không thế lưu trữ thêm data, và ta không thể thêm dung lượng kể cả khi ta có tiền. Đồng thời Raid 5 có thể chịu lỗi 1 ổ, Raid 6 2 ổ, nếu có nhiều hơn, việc phục hồi data sẽ trở nên rất khó khăn hoặc không thể. Và raid chỉ có thể bảo vệ lỗi trên disk, còn các lỗi nhề network, hardware, os … là điều không thể.

Ceph storage system sẽ là giải pháp cho nhưng vấn đề trên. Về tính đảm bảo, Raid sẽ tự nhân bản thuật toán, không phụ thuộc raid. Ceph is a softwaredefined storage, vì vậy, ta sẽ không cần sử dụng thiết bị chuyên dụng, đồng thời Ceph nhân bản data theo config, vì thế người quản trị sẽ dễ dàng định nghĩa số lượng bản sao, tối ưu phần cứng, dễ dang quản lý. Đồng thời Ceph có khả năng chịu lỗi nhiều hơn 2 disk, với tốc độ khôi phục đang ngạc nhiên, vì dữ liệu trong ceph không phân chi bản chính bản phụ. Đồng thời Ceph có thể lưu trữ khỗi lượng dữ liệu nhiều hơn dựa vào thuật toán CRUSH, vào quản trị thông qua CRUSH maps.

Bên cạnh phương pháp nhân bản, Ceph cung cấp "erasure-coding technique". Kỹ thuật này yêu cầu ít storage space khi so sánh với replicated pool. Khi xử lý, data sẽ được khôi phục và tái tạo = erasure-code calculation. Ta có thể sử dụng đồng thời 2 phương pháp trong storage.
