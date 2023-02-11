----Task#1
--Create View User_data
--as
--Select * from [User]
--go 

--select * From User_data

----Task#2
--Create View User_ATM
--as
--select [User].name,[User].phoneNum,[User].city,[UserCard].cardNum from [UserCard] join [user]
--on UserCard.userID=[user].userId
--go

--select * From User_ATM

----Task#3
--Create Procedure User_info
--@input_user_name varchar(30)
--as begin
--	if ( @input_user_name = (select [User].name from [user] where [User].name = @input_user_name) )
--		begin
--			select * from [user]
--		end
--	else
--		begin
--			Print 'User not found.'
--		end
--end 
--go

--exec User_info
--@input_user_name = 'Ali1'
--go

----Task#4
--Create Procedure User_Min_balance
--@output_balance int Output
--as begin
--	 set @output_balance = (select  min(Card.balance) from [Card])
--end 
--go

--declare @Balance_Result int = 0 

--exec User_Min_balance
--@output_balance = @Balance_Result output
--select @Balance_Result;
--go

----Task#5
--Create Procedure user_card_no
--@input_Name varchar(20),
--@input_id int,
--@output_CardNo int output
--as begin 
--	set @output_CardNo = (select count([UserCard].cardNum) from [User] join UserCard
--	on [User].userId = [UserCard].userID 
--	where [User].userId = @input_id and @input_Name = [User].name)
--end

--declare @Card_no int = 0 

--execute user_card_no
--@input_Name = 'Ali',
--@input_id = 1,
--@output_CardNo = @Card_no output
--select  @Card_no;
--go

----Task#6
--Create Procedure User_Login
--@input_cardNum Varchar(20),
--@input_PIN varchar(4),
--@output_access int output
--as begin 
--	if @input_cardNum = (select [Card].cardNum from [Card] 
--	where [Card].cardNum = @input_cardNum and [Card].PIN = @input_PIN)
--		begin
--			set @output_access = 1
--		end
--	else
--		begin
--			set @output_access = 0
--		end
--end

--declare @Card_Access int = 0 

--execute User_Login
--@input_cardNum = '1324327436569',
--@input_PIN = '1770',
--@output_access = @Card_Access output
--select @Card_Access;
--go

----Task#7
--Create Procedure User_PIN_update
--@input_cardNum Varchar(20),
--@input_Old_PIN varchar(4),
--@input_New_PIN varchar(4)
--as begin 
--	if @input_cardNum = (select [Card].cardNum from [Card] 
--	where [Card].cardNum = @input_cardNum and [Card].PIN = @input_Old_PIN)
--		begin
--			update [Card]
--			set [Card].PIN = @input_New_PIN where [Card].cardNum = @input_cardNum
--			print 'PIN Updated.'
--		end
--	else
--		begin
--			print 'PIN not Updated.'
--		end
--end

--declare @Card_Access int = 0 

--execute User_PIN_update
--@input_cardNum = '1324327436569',
--@input_Old_PIN = '4568',
--@input_New_PIN = '1770'
--go

------Task#8
--Create Procedure User_WithDraw
--@input_cardNum_w Varchar(20),
--@input_PIN_w varchar(4),
--@input_Amount int
--as begin 
--declare @Card_Access int = 0,
--@tran_id int = (select max(transId) from [Transaction])

--execute User_Login
--@input_cardNum = @input_cardNum_w,
--@input_PIN = @input_PIN_w,
--@output_access = @Card_Access output

--if @Card_Access = 1
--		begin
--			if ( @input_Amount <= (select [Card].balance from [Card] 
--			where [Card].cardNum = @input_cardNum_w ))
--				begin
--				update [Card]
--				set [Card].balance = [Card].balance - @input_Amount where [Card].cardNum = @input_cardNum_w
--				insert into [Transaction] values (@tran_id+1, Convert(date, getdate()),@input_cardNum_w, @input_Amount,1)
--				end
--			else
--				begin
--				insert into [Transaction] values (@tran_id+1, Convert(date, getdate()),@input_cardNum_w, @input_Amount,4)
--				end
--		end
--	else
--		begin
--			Print 'Invalid Request.'
--		end
--end

--execute User_WithDraw
--@input_cardNum_w = '1324327436569',
--@input_PIN_w = '1770',
--@input_Amount = 200
--go


--Select * from [Card]
--Select * from [Transaction]
