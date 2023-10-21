----Q1
--create trigger deletecustomer
--on customers
--instead of delete
--as
--begin
--	if((select CustomerNo from deleted) not in (select CustomerNo from [order]))
--	begin
--		delete from Customers where CustomerNo = (select CustomerNo from deleted)
--	end
--	else
--	begin
--		Print'Customer has ordered once.'
--	end
--end

--delete from Customers where CustomerNo = 'C3'

--select*from Customers

----Q2
--create trigger orderInsertCheck
--on Orderdetails
--instead of insert
--as begin
--	declare @i1 int = (select orderno from inserted),
--	@i2 int = (select itemno from inserted),
--	@i3 int = (select Quantity from inserted)
--	if((select Quantity from inserted) <= (select [Quantity in store] from items where ItemNo = @i2 ))
--	begin
--		insert into Orderdetails values (@i1,@i2,@i3)
--	end
--	else
--	begin
--		Print'The required quantity is not available'
--	end
--end

--insert into Orderdetails values (4,300,300)

--select * from Orderdetails

----Q3
--create trigger orderInsertAfterCheck
--on Orderdetails
--after update
--as begin
--	if(select [Quantity in store] from items where ItemNo = (select ItemNo from inserted))
--	= (select [Quantity in store] from items where ItemNo = (select ItemNo from inserted))
--	- (select Quantity from OrderDetails where OrderNo = (select max(OrderNo) from OrderDetails))
--	begin
--		Print'The quantity is not updated'
--		rollback
--	end
--end

--insert into Orderdetails values (4,300,300)

--select * from Orderdetails


----Q4
--create trigger deleteAfterCheck
--on items
--after delete
--as begin
--	if 100 >= (select [Quantity in store] from deleted )
--	begin
--		delete from items where ItemNo = (select ItemNo from deleted)
--	end
--	else
--	begin
--		Print'The quantity is above 100.'
--		rollback
--	end
--end

--delete from items where ItemNo = 400

--insert into Items values (400,'D',6000,400)

--select * from Items

----Q5
--create trigger orderInsertCheck
--on [Order]
--instead of insert
--as begin
--	if((select Date from inserted) = convert(date,GETDATE()))
--	begin
--		insert into [Order] values ((select OrderNo from inserted),
--									(select CustomerNo from inserted),
--									(select Date from inserted),
--									(select Total_Items_Ordered from inserted))
--	end
--	else
--	begin
--		insert into [Order] values ((select OrderNo from inserted),
--									(select CustomerNo from inserted),
--									convert(date,GETDATE()),
--									(select Total_Items_Ordered from inserted))
--	end
--end

--Q6
--create trigger customerInsertCheck
--on Customers
--after insert
--as begin
--	if((select CustomerNo from inserted) is null or
--		(select Name from inserted) is null or
--		(select City from inserted) is null or
--		(select Phone from inserted) is null)
--	begin
--		Print'Found a Null field.'
--		rollback
--	end
--end


----Q7
--Create Procedure Customer_Sign_Up
--@input_CustomerNo varchar(2),
--@input_CustomerName varchar(30),
--@input_CustomerCity varchar(3),
--@input_CustomerPhoneNo varchar(11),
--@output_Check_flag int Output
--as begin
--	if (@input_CustomerNo in (select CustomerNo from Customers ))
--		begin
--			set @output_Check_flag = 1
--		end
--	else if Len(@input_CustomerPhoneNo) != 6
--		begin
--			set @output_Check_flag = 3
--		end
--	else
--		begin
--			insert into Customers values(@input_CustomerNo,@input_CustomerName,@input_CustomerCity,@input_CustomerPhoneNo)
--			set @output_Check_flag = 0
--		end
--end 
--go

--declare @Flag_Result int = 0 

--exec Customer_Sign_Up
--@input_CustomerNo = 'C7',
--@input_CustomerName = 'Wikon',
--@input_CustomerCity = 'FKS',
--@input_CustomerPhoneNo = '444416',
--@output_Check_flag = @Flag_Result output
--select @Flag_Result as Sign_Up_Result;
--go