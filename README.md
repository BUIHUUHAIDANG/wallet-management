# **Hệ Thống Quản Lý Tài Khoản & Ví Điểm Thưởng**  
## 📌 Giới Thiệu  
Hệ thống quản lý đăng nhập, đăng ký tài khoản và ví điểm thưởng, hỗ trợ:  
✅ Đăng ký & xác thực người dùng  
✅ Quản lý ví điểm thưởng (tích lũy, chuyển điểm)  
✅ Bảo mật 2 lớp (OTP) cho giao dịch quan trọng  
✅ Phân quyền người dùng (User/Admin)  
## Phân công công việc  
### Thành viên thứ nhất:  
Họ tên: Bùi Hữu Hải Đăng  
Mã SV: N24DECE058  
Nhiệm Vụ:  
-Định nghĩa lớp User, thực hiện chức năng tạo tài khoản, đăng nhập, giao diện ban đầu, hashFunction, tự động tạo một mật khẩu random, thay đổi mật khẩu khi đăng nhập lần đầu, tạo phương thức lưu trữ thông tin user và sao lưu thông tin user vào file dự phòng, chức năng cập nhập mật khẩu, fullname, phonenumber.  
-Viết Readme.md  
### Thành viên thứ hai:  
Họ tên: Lê Trần Hoàng Minh  
Mã SV: N24DECE082  
Nhiệm Vụ:  
- Chịu trách nhiệm cho phần phân quyền giữa user và admin, thiết kế Menu của User và Admin, thực hiện những chức năng như xem thông tin user và gửi yêu cầu thay đổi thông tin tới admin trong Menu user và xem thông tin tất cả user và chấp nhận yêu cầu thay đổi của users.  
 ### Thành viên thứ ba:  
 Họ tên: Vũ Anh Khoa  
 Mã SV: N24DECE078  
 Nhiệm vụ:  
 - Định nghĩa lớp Ví, kiểm tra trùng tên và tìm user, thiết kế Menu Wallet với những chức năng như chuyển ví điểm thưởng từ ví A sang ví B, xem thông tin ví (số dư, lịch sử giao dịch) của user, tạo hàm lưu thông tin Ví điểm vào trong file mỗi user một file lưu trữ riêng.  
### Thành viên thứ tư:  
Họ tên: Nguyễn Gia Phát  
Mã SV: N24DECE086  
Nhiệm vụ: 
-Tạo ra chức năng tự tạo ra OTP có thời gian giới hạn và mỗi user có một OTP riêng, tích vào hợp vào các chức năng thay đổi thông tin của các thành viên trong nhóm.  
## ⚙️ Các Tính Năng Chính  
### 🔐 Đăng Ký & Đăng Nhập  
:radio_button:Tạo tài khoản mới (tự đăng ký hoặc admin tạo hộ).  
:radio_button:Tránh trùng tên tài khoản.  
:radio_button:Yêu cầu đổi mật khẩu nếu dùng mật khẩu mặc định khi đăng nhập lần đầu tiên.  
:radio_button:Lưu trữ tất cả thông tin cá nhân của người dùng vào trong file.  
:radio_button:Có bản sao lưu thông tin khách hàng để tránh mất thông tin ở file gốc.  
:radio_button:Có chức năng tự sinh mật khẩu nếu người dùng bỏ trống.  
:radio_button:Có chức năng cập nhật thông tin cá nhân người dùng vào file.   
### 💳 Quản Lý Ví Điểm Thưởng  
:radio_button:Mỗi người dùng có một ví riêng với số điểm tích lũy.  
:radio_button:Mỗi người dùng có một file lưu trữ riêng số dư, thông tin chuyển điểm từ một ví khác được đặt tên dựa vào WalletID    
:radio_button:Chuyển điểm giữa các ví (kiểm tra số dư trước khi giao dịch).  
:radio_button:Lịch sử giao dịch chi tiết.  
:radio_button:Có lưu trữ thông tin ví số dư, thông tin chuyển tiền từ một ví khác vào 1 file.  
### 🔒 Bảo Mật  
:radio_button:Mật khẩu được băm ra bởi hàm (hash function).  
:radio_button:Xác thực OTP khi đổi các thông tin cá nhân.  
:radio_button:Không cho thay đổi Username.  
### 👥 Phân Quyền

| **Quyền**                   | **User** | **Admin** |
|-----------------------------|:--------:|:---------:|
| Xem thông tin cá nhân       | ✅       | ✅        |
| Chuyển điểm                 | ✅       | ❌        |
| Tạo tài khoản mới           | ❌       | ✅        |
| Xem danh sách người dùng    | ❌       | ✅        |  

## 📂 Cấu Trúc Dữ Liệu  
### 1. 👤 Người Dùng (User)

```json
{
  "username": "user123",
  "fullname": "Nguyễn Văn A",
  "passwordHash": "$2a$12$xyz...",
  "phonenumber": "0912345678",
  "walletID": "WalletID+username",
  "isManager": false,
  "firstlogin": true
}
```

---

### 2. 💰 Ví (Wallet)

```json
{
 "wallet_id": "WalletID+username",
  "transaction": "user123 → user456",
  "remainder": "1000000"
}
```

---  
## 📂 Các File dữ liệu
### các file như là:  
user.txt: dùng để lưu trữ tất cả thông tin người dùng.  
user_backup.txt: dùng để sao lưu dữ liệu thông tin tất cả người dùng để phục hồi dữ liệu nếu file gốc mất.   
wallet_id_ + username + .txt:lưu trữ dữ liệu ví số dư và lịch sử chuyển điểm của người dùng.  
request.txt: lưu những yêu cầu của user để thay đổi thông tin.  
## 🛠️ Công Nghệ Sử Dụng  
:radio_button: C++.  
## 🚀 Hướng Dẫn Cài Đặt  
### 1. Truy cập vào GitHub Repository của dự án:
https://github.com/BUIHUUHAIDANG/wallet-management  
### 2. Bấm vào nút Code màu xanh lá → chọn Download ZIP để tải về máy.  
### 3. Giải nén file ZIP vừa tải.
### 4. Mở thư mục đó trong terminal hoặc trình biên dịch để tiến hành dịch/chạy(chú ý đây là chương trình C++, mọi thư viện đều nắm trong source code nên không cần cài thêm thư viện nào bên ngoài cả).  
## Mô tả cách chạy chương trình, kèm các thao tác thực hiện  
### Chạy chương trình:
Khi chạy chương trình cửa sổ terminal sẽ xuất hiện ra với 2 lựa chọn:  
1. Register: Nơi bạn điền username, thông tin cá nhân(Fullname, phonenumber), password(có thể bỏ trống để có thể tạo ra mật khẩu tự động), sẽ hỏi bạn có phải admin hay ko ?.
2. sign in: đây là khi bạn đã đăng kí thành công và đăng nhập nếu đây là lần đăng nhập lần đầu tiên của bạn chương trình sẽ gọi hàm changepassword để bạn thay đổi mật khẩu tự động thành mật khẩu mà bạn mong muốn và mất khẩu sẽ được hash để cho vào file user.txt để bảo mật.
### Khi đăng nhập thành công:  
sẽ hiện ra hai menu nếu bạn là user thì chương trình sẽ là menu user còn nếu bạn là admin thì chương trình sẽ là menu admin.  
- Menu User:  
   1. View personal information: nơi user có thể xem thông tin cá nhân của user
   2. Change password: nơi user thay đổi password và sẽ gọi hàm cập nhật password vào file user.txt  
   3. Request to change information: nơi bạn sẽ nhập mã OTP để gửi yêu cầu muốn đổi thay đổi thông tin tới admin xong r sẽ nhập new fullname và new phonenumber thông tin thay đổi sẽ được lưu vào file request.txt đợi admin chấp nhận.  
   4. Wallet: sẽ hiện ra walletmenu trong wallet menu sẽ có 2 chức năng chính:  
      1.Show wallet information: nơi bạn có thể xem được WalletID, số dư, lịch sự chuyển điểm.  
      2.Trasfer: nơi bạn sẽ nhập WalletID của người nhận vào và số điểm bạn muốn chuyển nếu số dư của user đủ sẽ trừ số tiền hiện tại nếu số dư không đủ sẽ báo là không thể thực hiện giao dịch.
      
 - Menu Admin:  
1. View users list: nơi admin có thể xem được mọi user trong chương trình.  
2. Create new account: tạo hộ tài khoản mới cho user.  
3. Approve information change requests: nơi admin có xác nhận thay đổi thông tin hay không.
## Sơ đồ miêu tả chương trình  
+------------------------+
| Khởi động chương trình |
+------------------------+
            |
            v
      +---------------+
      |  Menu Chính   |
      +---------------+
            |
      +------+------+
      |             |
      v             v
+-------------+  +--------------+
|   Đăng ký   |  |   Đăng nhập  |
+-------------+  +--------------+
                     |
          +----------+----------+
          |                     |
          v                     v
   +----------------+    +----------------+
   |   User Menu    |    |   Admin Menu   |
   +----------------+    +----------------+
     |     |      |  \
     v     v      v   v
 View  Change  Request Wallet
 Info Password Info    |
                       v
             +----------------------+
             |       Wallet         |
             +----------------------+
                  |           |
                  v           v
          Show Info       Transfer

Admin Menu:
  +-----------------------------+
  | - View users list          |
  | - Create new account       |
  | - Approve info change reqs |
  +-----------------------------+

## 📜 Tài liệu tham khảo
### 1. Youtube  
### 2. geeksforgeeks.org  
### 3. stackoverflow.com  


