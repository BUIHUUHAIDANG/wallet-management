# **Hệ Thống Quản Lý Tài Khoản & Ví Điểm Thưởng**  
## 📌 Giới Thiệu  
Hệ thống quản lý đăng nhập, đăng ký tài khoản và ví điểm thưởng, hỗ trợ:  
✅ Đăng ký & xác thực người dùng  
✅ Quản lý ví điểm thưởng (tích lũy, chuyển điểm)  
✅ Bảo mật 2 lớp (OTP) cho giao dịch quan trọng  
✅ Phân quyền người dùng (User/Admin)  
## ⚙️ Các Tính Năng Chính  
### 🔐 Đăng Ký & Đăng Nhập  
:radio_button:Tạo tài khoản mới (tự đăng ký hoặc admin tạo hộ).  
:radio_button:Tránh trùng tên tài khoản.  
:radio_button:Yêu cầu đổi mật khẩu nếu dùng mật khẩu mặc định.  
### 💳 Quản Lý Ví Điểm Thưởng  
:radio_button:Mỗi người dùng có một ví riêng với số điểm tích lũy.  
:radio_button:Chuyển điểm giữa các ví (kiểm tra số dư trước khi giao dịch).  
:radio_button:Lịch sử giao dịch chi tiết.  
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
### 1. Người Dùng (User)  
```json
{
  "username": "user123",  
  "fullname": "Nguyễn Văn A",  
  "passwordHash": "$2a$12$xyz...",  
  "phonenumber": "0912345678",  
  "WalletID": "W001",  
  "isManager": false,  
  "firstlogin": true,  
}


