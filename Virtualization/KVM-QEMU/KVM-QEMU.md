# KVM/QEMU
KVM (Kernel-based virtual machine) là giải pháp ảo hóa cho hệ thống linux trên nền tảng phần cứng x86 có các module mở rộng hỗ trợ ảo hóa (Intel VT-x hoặc AMD-V)

Về bản chất, KVM không thực sự là một hypervisor có chức năng giải lập phần cứng để chạy các máy ảo. Chính xác KVM chỉ là một module của kernel linux có có chế ánh xạ các chỉ thị từ CPU ảo (guest VM) đến CPU vật lý (máy chủ chứa VM).

KVM được thực hiện như một quy trình xử lý thông thường của Linux. Trên thực tế, mỗi CPU ảo hoạt động như một tiến trình xử lý của Linux. Điều này cho phép KVM được thừa hưởng tất cả các tính năng của nhân Linux.

![image](https://user-images.githubusercontent.com/83684068/123893092-f63cf580-d985-11eb-856e-23e7e8ae1068.png)

## Các tính năng của ảo hóa KVM
### 1. Bảo mật
Vì được coi như một tiến trình xử lý của Linux, nên KVM tận dụng được mô hình bảo mật tiêu chuẩn của Linux để cung cấp khả năng điều khiển và cô lập tài nguyên. 

### 2. Quản lý bộ nhớ
KVM thừa hưởng tính năng quản lý bộ nhớ mạnh mẽ của Linux. Vùng nhớ của máy ảo được lưu trữ trên cùng một vùng nhớ dành cho các tiến trình Linux khác và có thể swap.

KVM hỗ trợ NUMA (Non-Uniform Memory Access - bộ nhớ thiết kế cho hệ thống đa xử lý) cho phép tận dụng hiệu quả vùng nhớ kích thước lớn. Cũng như hỗ trợ các tính năng ảo hóa mới nhất từ các nhà cung cấp CPU như Microsoft và AMD, nhằm tối ưu mức độ sử dụng CPU và cho thông lượng cao hơn.

### 3. Lưu trữ
KVM sử dụng khả năng lưu trữ hỗ trợ bởi Linux và có thể tận dụng hạ tầng lưu trữ tin cậy với sự hỗ trợ từ tất cả các nhà cung cấp hàng đầu trong lĩnh vực Storage. 

Định dạng image mặc định của KVM là QCOW2 – hỗ trợ snapshot đa mức, nén và mã hóa dữ liệu.

### 4. Hỗ trợ dịch chuyển trực tiếp
KVM hỗ trợ live migration cung cấp khả năng di chuyển các máy ảo đang chạy giữa các host vật lý mà không làm gián đoạn dịch vụ. Quá trình dịch chuyển là trong suốt với người dùng, các máy ảo vẫn duy trì trạng thái thông thường trong thời gian được đưa sang một host vật lý mới.

KVM cũng cho phép lưu lại trạng thái hiện tại của máy ảo để cho phép lưu trữ và khôi phục trạng thái đó vào lần sử dụng tiếp theo.

### 5. Hiệu suất hoạt động và khả năng mở rộng
KVM kế thừa hiệu suất và khả năng mở rộng của Linux, hỗ trợ các máy ảo lên tới 16 CPUs ảo, 256GB RAM cùng với hệ thống máy chủ lên tới 256 cores và trên 1TB RAM.

# QEMU
QEMU (Quick Emulator) là một chương trình ảo hóa thuộc lớp 2 trong [Ring](https://github.com/huynp1999/huynp/blob/master/Virtualization/Virtualization-Hypervisor.md#3-ring) (chạy trên một host OS) để thực hiện việc ảo hóa phần cứng.
Hai kiểu mô phỏng QEMU:
- Toàn phần: QEMU sẽ tiến hành ảo hóa toàn bộ hệ thống, bao gồm CPU và các thành phần khác.
- Một phần: ảo hóa ứng dụng trên 1 nền CPU khác.

Quan hệ giữa QEMU và KVM là khi được kết hợp với nhau thì sẽ tạo thành type-1 hypervisor.
- QEMU cần KVM để tăng hiệu năng hoạt động
- KVM cần QEMU để hoàn thiện các tính năng ảo hóa hoàn chỉnh.


Mô hình hoạt động chung giữa KVM và QEMU:

![image](https://camo.githubusercontent.com/c1c8d9191efcb3b3654b207d7e84432cc72a4e678cd56f14a06e438763b04b1a/687474703a2f2f696d6775722e636f6d2f777341356846372e6a7067)

Trong đó:
- **User-facing tools:** Là các công cụ quản lý máy ảo hỗ trợ KVM, như giao diện đồ họa (như virt-manager), giao diện dòng lệnh (virsh) và virt-tool (Các công cụ này được quản lý bởi thư viện libvirt).
- **Management layer:** Lớp này được thư viện libvirt cung cấp API để các công cụ quản lý máy ảo hoặc các hypervisor tương tác với KVM thực hiện các thao tác quản lý tài nguyên ảo hóa. Bản chất KVM chỉ là một module của nhân Linux có cơ chế mapping ánh xạ các chỉ thị của CPU ảo lên CPU thật, nên KVM không có khả năng giả lập và quản lý tài nguyên ảo hóa. Mà phải dùng nhờ các công nghệ hypervisor khác, thường là QEMU.
- **Virtual machine:** Là các máy ảo người dùng tạo ra. Thông thường, nếu không sử dụng các công cụ như virsh hay virt-manager, KVM sẽ sử dụng phối hợp với một hypervisor khác, điển hình là QEMU.
- **Kernel support:** Vị trí của KVM, cung cấp một module làm hạt nhân cho hạ tầng ảo hóa (kvm.ko).

