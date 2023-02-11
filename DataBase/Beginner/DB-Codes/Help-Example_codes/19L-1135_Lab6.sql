--SET ANSI_NULLS ON
--GO
--SET QUOTED_IDENTIFIER ON
--GO
--SET ANSI_PADDING ON
--GO
--CREATE TABLE [dbo].[Items](
--	[ItemNo] [int] NOT NULL,
--	[Name] [varchar](10) NULL,
--	[Price] [int] NULL,
--	[Quantity in Store] [int] NULL,
--PRIMARY KEY CLUSTERED 
--(
--	[ItemNo] ASC
--)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
--) ON [PRIMARY]
--GO
--SET ANSI_PADDING OFF
--GO
--INSERT [dbo].[Items] ([ItemNo], [Name], [Price], [Quantity in Store]) VALUES (100, N'A', 1000, 100)
--INSERT [dbo].[Items] ([ItemNo], [Name], [Price], [Quantity in Store]) VALUES (200, N'B', 2000, 50)
--INSERT [dbo].[Items] ([ItemNo], [Name], [Price], [Quantity in Store]) VALUES (300, N'C', 3000, 60)
--INSERT [dbo].[Items] ([ItemNo], [Name], [Price], [Quantity in Store]) VALUES (400, N'D', 6000, 400)

--SET ANSI_NULLS ON
--GO
--SET QUOTED_IDENTIFIER ON
--GO
--SET ANSI_PADDING ON
--GO
--CREATE TABLE [dbo].[Customers](
--	[CustomerNo] [varchar](2) NOT NULL,
--	[Name] [varchar](30) NULL,
--	[City] [varchar](3) NULL,
--	[Phone] [varchar](11) NULL,
--PRIMARY KEY CLUSTERED 
--(
--	[CustomerNo] ASC
--)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
--) ON [PRIMARY]
--GO
--SET ANSI_PADDING OFF
--GO
--INSERT [dbo].[Customers] ([CustomerNo], [Name], [City], [Phone]) VALUES (N'C1', N'AHMED ALI', N'LHR', N'111111')
--INSERT [dbo].[Customers] ([CustomerNo], [Name], [City], [Phone]) VALUES (N'C2', N'ALI', N'LHR', N'222222')
--INSERT [dbo].[Customers] ([CustomerNo], [Name], [City], [Phone]) VALUES (N'C3', N'AYESHA', N'LHR', N'333333')
--INSERT [dbo].[Customers] ([CustomerNo], [Name], [City], [Phone]) VALUES (N'C4', N'BILAL', N'KHI', N'444444')
--INSERT [dbo].[Customers] ([CustomerNo], [Name], [City], [Phone]) VALUES (N'C5', N'SADAF', N'KHI', N'555555')
--INSERT [dbo].[Customers] ([CustomerNo], [Name], [City], [Phone]) VALUES (N'C6', N'FARAH', N'ISL', NULL)
--/****** Object:  Table [dbo].[Order]    Script Date: 02/17/2017 13:04:03 ******/
--SET ANSI_NULLS ON
--GO
--SET QUOTED_IDENTIFIER ON
--GO
--SET ANSI_PADDING ON
--GO
--CREATE TABLE [dbo].[Order](
--	[OrderNo] [int] NOT NULL,
--	[CustomerNo] [varchar](2) NULL,
--	[Date] [date] NULL,
--	[Total_Items_Ordered] [int] NULL,
--PRIMARY KEY CLUSTERED 
--(
--	[OrderNo] ASC
--)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
--) ON [PRIMARY]
--GO
--SET ANSI_PADDING OFF
--GO
--INSERT [dbo].[Order] ([OrderNo], [CustomerNo], [Date], [Total_Items_Ordered]) VALUES (1, N'C1', CAST(0x7F360B00 AS Date), 30)
--INSERT [dbo].[Order] ([OrderNo], [CustomerNo], [Date], [Total_Items_Ordered]) VALUES (2, N'C3', CAST(0x2A3C0B00 AS Date), 5)
--INSERT [dbo].[Order] ([OrderNo], [CustomerNo], [Date], [Total_Items_Ordered]) VALUES (3, N'C3', CAST(0x493C0B00 AS Date), 20)
--INSERT [dbo].[Order] ([OrderNo], [CustomerNo], [Date], [Total_Items_Ordered]) VALUES (4, N'C4', CAST(0x4A3C0B00 AS Date), 15)

--SET ANSI_NULLS ON
--GO
--SET QUOTED_IDENTIFIER ON
--GO
--CREATE TABLE [dbo].[OrderDetails](
--	[OrderNo] [int] NOT NULL,
--	[ItemNo] [int] NOT NULL,
--	[Quantity] [int] NULL,
--PRIMARY KEY CLUSTERED 
--(
--	[OrderNo] ASC,
--	[ItemNo] ASC
--)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
--) ON [PRIMARY]
--GO
--INSERT [dbo].[OrderDetails] ([OrderNo], [ItemNo], [Quantity]) VALUES (1, 200, 20)
--INSERT [dbo].[OrderDetails] ([OrderNo], [ItemNo], [Quantity]) VALUES (1, 400, 10)
--INSERT [dbo].[OrderDetails] ([OrderNo], [ItemNo], [Quantity]) VALUES (2, 200, 5)
--INSERT [dbo].[OrderDetails] ([OrderNo], [ItemNo], [Quantity]) VALUES (3, 200, 60)

--GO
--ALTER TABLE [dbo].[OrderDetails]  WITH CHECK ADD FOREIGN KEY([ItemNo])
--REFERENCES [dbo].[Items] ([ItemNo])
--GO
--ALTER TABLE [dbo].[OrderDetails]  WITH CHECK ADD FOREIGN KEY([OrderNo])
--REFERENCES [dbo].[Order] ([OrderNo])
--GO

--==============================================================================================================
--==============================================================================================================
--==============================================================================================================
--==============================================================================================================


----Task#1
--Create View Order_Prices_1
--as
--select O.OrderNo, (O.Quantity*I.Price) as ItemPrice
--From OrderDetails O join Items I 
--on O.ItemNo = I.ItemNo
--go 

--select OrderNo, sum(ItemPrice) as total_Order_Price From Order_Prices_1
--group by OrderNo

----Task#2
--Create View Order_Prices_2
--as
--select I.ItemNo, I.Name, I.Price 
--From Items I where I.ItemNo in (
--	select ItemNo From OrderDetails
--	Group by ItemNo having sum(Quantity) > 20
--)
--go

--select * From Order_Prices_2

----Task#3
--Create Procedure Check_Order_Validity
--@input_OrderNo int,
--@input_ItemNo int,
--@input_Ordered_Quantity int
--as begin
--	if ( @input_Ordered_Quantity > (select [Quantity in Store] from [Items] where ItemNo = @input_ItemNo) )
--		begin
--			select 'only '+ CONVERT(varchar(10),[Quantity in Store]) +'  is present, which is less than your required quantity is' from [Items] where ItemNo = @input_ItemNo
--		end
--	else
--		begin
--			insert into [OrderDetails] values(@input_OrderNo,@input_ItemNo,@input_Ordered_Quantity)
--			Update Items
--			set [Quantity in Store] = [Quantity in Store] - @input_Ordered_Quantity
--			where Items.ItemNo = @input_ItemNo
--		end
--end 
--go

--exec Check_Order_Validity
--@input_OrderNo = 4,
--@input_ItemNo = 400,
--@input_Ordered_Quantity = 20
--go

--select * from Items
--select * from OrderDetails

----Task#4
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
--	else if (@input_CustomerCity is Null)
--		begin
--			set @output_Check_flag = 2
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
--@input_CustomerName = 'Max Wilson',
--@input_CustomerCity = 'ISL',
--@input_CustomerPhoneNo = '444416',
--@output_Check_flag = @Flag_Result output
--select @Flag_Result as Sign_Up_Result;
--go

----Task#5
--Create Procedure Cancel_Order
--@input_CustomerNo varchar(2),
--@input_OrderNo int
--as begin 
--	if @input_CustomerNo = (select CustomerNo from [Order] where OrderNo = @input_OrderNo ) 
--		begin
--			delete from [Order]
--			where OrderNo = @input_OrderNo
--			delete from [OrderDetails]
--			where OrderNo = @input_OrderNo
--		end
--	else
--		begin
--			select 'Order no ' + CONVERT(varchar(2),@input_OrderNo)  + ' is not of ' + CustomerNo + ' ' + [Name] from Customers 
--			where CustomerNo = @input_CustomerNo
--		end
--end

--execute Cancel_Order
--@input_orderNo= 4,
--@input_CustomerNo= 'C4'

----Task#6
--Create View Star_Customers
--as
--select OrderNo, sum(ItemPrice) as total_Order_Price From Order_Prices_1
--group by OrderNo
--having sum(ItemPrice) > 2000
--go

--select * from Star_Customers

----Task#7
--Create Procedure Customer_Purchase_Points
--@input_CustomerName varchar(30),
--@output_Customer_Points int Output
--as begin 
--	if ((select CustomerNo from [Customers] where [Customers].[Name] = @input_CustomerName) in (select CustomerNo from [Order]))
--		begin
--			set @output_Customer_Points = ((select sum(OrderDetails.Quantity*Items.Price) as ItemPrice
--			From OrderDetails join Items on OrderDetails.ItemNo = Items.ItemNo
--			join [Order] on [Order].OrderNo = OrderDetails.OrderNo group by CustomerNo
--			having CustomerNo = (select CustomerNo from [Customers] where [Customers].[Name] = @input_CustomerName)) / 100)
--		end
--	else
--		begin
--			select 'Customer with name: '+ @input_CustomerName +' is not found in the records.'
--		end
--end

--declare @Total_Customer_Points int = 0 

--exec Customer_Purchase_Points
--@input_CustomerName = 'AYESHA',
--@output_Customer_Points = @Total_Customer_Points output
--select @Total_Customer_Points as Total_Points;
--go

------Task#8
--Create View Customers_With_No_Phone_With_Check
--as
--select * from Customers where Phone is not null
--with check option
--go 

--Create View Customers_With_No_Phone
--as
--select * from Customers where Phone is not null
--go

--insert into [Customers_With_No_Phone]
--values ('a2','will','isl',null)

--select * from [Customers]
--select * from [Customers_With_No_Phone_With_Check]
--select * from [Customers_With_No_Phone]

--insert into [Customers_With_No_Phone_With_Check]
--values ('a1','Max','lhr',null)

--insert into [Customers_With_No_Phone_With_Check]
--values ('b1','nine','khr','167654')

--select * from [Customers]
--select * from [Customers_With_No_Phone_With_Check]
--select * from [Customers_With_No_Phone]

--delete from [Customers_With_No_Phone_With_Check]
--where Name = 'will'

--delete from [Customers_With_No_Phone]
--where Name = 'nine'


--delete from [Customers_With_No_Phone_With_Check]
--where Name = 'nine'

--delete from [Customers_With_No_Phone]
--where Name = 'will'


--delete from [Customers]
--where Name = 'will'

--select * from [Customers]
--select * from [Customers_With_No_Phone_With_Check]
--select * from [Customers_With_No_Phone]
