create database udf_lab
use udf_lab

go

create table Customer
(
	CustomerID int primary key,
	CustomerName varchar(50),
	Phone varchar(50)
	
)

go
create table Product
(
	ProductID int primary key,
	ProductName varchar(50),
	Price int
	
)
go
create table [Order]
(
	OrderID int primary key,
	CustomerID int
	Foreign key (CustomerID) references Customer(CustomerID)
)
go
create table OrderItem
(
	ID int primary key,
	ProductID int,
	OrderID int,
	quantity int
	Foreign key (OrderID) references [Order](OrderID),
	Foreign key (ProductID) references [dbo].[Product](ProductID)
)

go
Insert into Customer(CustomerID, CustomerName, Phone) VALUES (1, 'Ali', '123-123-123' )
Insert into Customer(CustomerID, CustomerName, Phone) VALUES (2, 'hassan' , '123-123-123' )
Insert into Customer(CustomerID, CustomerName, Phone) VALUES (3, 'Maha', '123-123-123' )
Insert into Customer(CustomerID, CustomerName, Phone) VALUES (4, 'waleed', '123-123-123' )
Insert into Customer(CustomerID, CustomerName, Phone) VALUES (5, 'hamza', '123-123-123' )

go
Insert into Product (ProductID, ProductName, Price) VALUES (1,'Laptop',50000)
Insert into Product (ProductID, ProductName, Price) VALUES (2,'Tab',20000)
Insert into Product (ProductID, ProductName, Price) VALUES (3,'Mobile',40000)
Insert into Product (ProductID, ProductName, Price) VALUES (4,'USB',1000)
Insert into Product (ProductID, ProductName, Price) VALUES (5,'Smart Watch',30000)
 
 go
Insert into [Order](OrderID,CustomerID) VALUES (1,1)
Insert into [Order](OrderID,CustomerID) VALUES (2,2)
Insert into [Order](OrderID,CustomerID) VALUES (3,3)
Insert into [Order](OrderID,CustomerID) VALUES (4,1)
Insert into [Order](OrderID,CustomerID) VALUES (5,2)
go
Insert into OrderItem (ID, ProductID, OrderID, quantity) VALUES (1,1,1,5)
Insert into OrderItem (ID, ProductID, OrderID, quantity) VALUES (2,1,3,4)
Insert into OrderItem (ID, ProductID, OrderID, quantity) VALUES (3,1,2,6)
Insert into OrderItem (ID, ProductID, OrderID, quantity) VALUES (4,2,4,4)
Insert into OrderItem (ID, ProductID, OrderID, quantity) VALUES (5,3,5,3)
Insert into OrderItem (ID, ProductID, OrderID, quantity) VALUES (6,4,2,1)
Insert into OrderItem (ID, ProductID, OrderID, quantity) VALUES (7,4,3,2)


go
create trigger checking
on Product
instead of insert
as
begin
select * from inserted
end