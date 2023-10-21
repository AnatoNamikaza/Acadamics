--Create database ATM
--go 
--use ATM
--go

--create table [User](
--[userId] int primary key,
--[name] varchar(20) not null,
--[phoneNum] varchar(15) not null,
--[city] varchar(20) not null
--)
--go

--create table CardType(
--[cardTypeID] int primary key,
--[name] varchar(15),
--[description] varchar(40) null
--)
--go
--create Table [Card](
--cardNum Varchar(20) primary key,
--cardTypeID int foreign key references  CardType([cardTypeID]),
--PIN varchar(4) not null,
--[expireDate] date not null,
--balance float not null
--)
--go


--Create table UserCard(
--userID int foreign key references [User]([userId]),
--cardNum varchar(20) foreign key references [Card](cardNum),
--primary key(cardNum)
--)
--go
--create table [Transaction](
--transId int primary key,
--transDate date not null,
--cardNum varchar(20) foreign key references [Card](cardNum),
--amount int not null
--)


--INSERT [dbo].[User] ([userId], [name], [phoneNum], [city]) VALUES (1, N'Ali', N'03036067000', N'Narowal')
--GO
--INSERT [dbo].[User] ([userId], [name], [phoneNum], [city]) VALUES (2, N'Ahmed', N'03036047000', N'Lahore')
--GO
--INSERT [dbo].[User] ([userId], [name], [phoneNum], [city]) VALUES (3, N'Aqeel', N'03036063000', N'Karachi')
--GO
--INSERT [dbo].[User] ([userId], [name], [phoneNum], [city]) VALUES (4, N'Usman', N'03036062000', N'Sialkot')
--GO
--INSERT [dbo].[User] ([userId], [name], [phoneNum], [city]) VALUES (5, N'Hafeez', N'03036061000', N'Lahore')
--GO


--INSERT [dbo].[CardType] ([cardTypeID], [name], [description]) VALUES (1, N'Debit', N'Spend Now, Pay Now')
--GO
--INSERT [dbo].[CardType] ([cardTypeID], [name], [description]) VALUES (2, N'Credit', N'Spend Now, Pay later')
--GO

--INSERT [dbo].[Card] ([cardNum], [cardTypeID], [PIN], [expireDate], [balance]) VALUES (N'1234', 1, N'1770', CAST(N'2022-07-01' AS Date), 43025.31)
--GO
--INSERT [dbo].[Card] ([cardNum], [cardTypeID], [PIN], [expireDate], [balance]) VALUES (N'1235', 1, N'9234', CAST(N'2020-03-02' AS Date), 14425.62)
--GO
--INSERT [dbo].[Card] ([cardNum], [cardTypeID], [PIN], [expireDate], [balance]) VALUES (N'1236', 1, N'1234', CAST(N'2019-02-06' AS Date), 34325.52)
--GO
--INSERT [dbo].[Card] ([cardNum], [cardTypeID], [PIN], [expireDate], [balance]) VALUES (N'1237', 2, N'1200', CAST(N'2021-02-05' AS Date), 24325.3)
--GO
--INSERT [dbo].[Card] ([cardNum], [cardTypeID], [PIN], [expireDate], [balance]) VALUES (N'1238', 2, N'9004', CAST(N'2020-09-02' AS Date), 34025.12)
--GO

--INSERT [dbo].[UserCard] ([userID], [cardNum]) VALUES (1, N'1234')
--GO
--INSERT [dbo].[UserCard] ([userID], [cardNum]) VALUES (1, N'1235')
--GO
--INSERT [dbo].[UserCard] ([userID], [cardNum]) VALUES (2, N'1236')
--GO
--INSERT [dbo].[UserCard] ([userID], [cardNum]) VALUES (3, N'1238')
--GO
--Insert  [dbo].[UserCard] ([userID], [cardNum]) VALUES (4, N'1237')

--INSERT [dbo].[Transaction] ([transId], [transDate], [cardNum], [amount]) VALUES (1, CAST(N'2017-02-02' AS Date), N'1234', 500)
--GO
--INSERT [dbo].[Transaction] ([transId], [transDate], [cardNum], [amount]) VALUES (2, CAST(N'2018-02-03' AS Date), N'1235', 3000)
--GO
--INSERT [dbo].[Transaction] ([transId], [transDate], [cardNum], [amount]) VALUES (3, CAST(N'2020-01-06' AS Date), N'1236', 2500)
--GO
--INSERT [dbo].[Transaction] ([transId], [transDate], [cardNum], [amount]) VALUES (4, CAST(N'2016-09-09' AS Date), N'1238', 2000)
--GO
--INSERT [dbo].[Transaction] ([transId], [transDate], [cardNum], [amount]) VALUES (5, CAST(N'2020-02-10' AS Date), N'1234', 6000)
--GO


--Select * from [User]
--Select * from UserCard
--Select * from [Card]
--Select * from CardType
--Select * from [Transaction]

---------------------------------------------------------------------------------------------------

--Task#1
Select Catg2.cardTypeID, count(Catg2.cardTypeID) as TotalUniqueUsers from 
(
	Select [Card].cardTypeID, [UserCard].userID, count([Card].cardTypeID) as totalUsers 
	from [Card] Full Join [UserCard] on [Card].cardNum = [UserCard].cardNum
	Group by [Card].cardTypeID, [UserCard].userID
) as Catg2
Group by Catg2.cardTypeID

--Task#2

Select UserCard.cardNum, [User].name From [User] Join UserCard on [User].userId = UserCard.userID
where UserCard.cardNum in 
(
	Select [Card].cardNum From [Card] where balance between 20000 and 40000
)

--Task#3

--Using set operations
Select [User].name From [User] 
Except
Select [User].name From [User] 
Where [User].userId in
(
	Select UserCard.userID From [UserCard] 
)

--Using join
Select [User].name From [User] Full Join UserCard on [User].userId = UserCard.userID
Where [User].userId not in
(
	Select UserCard.userID From [UserCard] 
)

--Task#4

--Using set operations
Select [Card].cardNum as CardNum, [Card].cardTypeID as CardTypeId, [User].name as OwnerName 
From [User], [UserCard], [Card]
where [User].userId = [UserCard].userID AND [UserCard].cardNum = [Card].cardNum
Except
Select [Card].cardNum as CardNum, [Card].cardTypeID as CardTypeId, [User].name as OwnerName 
From [User], [UserCard], [Card]
where [User].userId = [UserCard].userID AND [UserCard].cardNum = [Card].cardNum
AND [UserCard].cardNum in 
(
	Select [Transaction].cardNum From [Transaction]
	where year(Getdate())-1 = Year([Transaction].transDate)
)

--Using join
Select [Card].cardNum, [Card].cardTypeID, [User].name 
From [User] Full Join [UserCard] on [User].userId = [UserCard].userID
Full Join [Card] on [UserCard].cardNum = [Card].cardNum
Full Join [Transaction] on [Card].cardNum = [Transaction].cardNum
where [UserCard].cardNum not in
(
	Select [UserCard].cardNum 
	From [User] Full Join [UserCard] on [User].userId = [UserCard].userID
	Full Join [Card] on [UserCard].cardNum = [Card].cardNum
	Full Join [Transaction] on [Card].cardNum = [Transaction].cardNum
	where year(Getdate())-1 = Year([Transaction].transDate)
)

--Task#5

Select [Card].cardTypeID, count([Transaction].cardNum) as TotalNumberOfCards
From [Card] Full Join [Transaction] on [Card].cardNum = [Transaction].cardNum
Where year([Transaction].transDate) between 2015 and 2017 
Group by [Card].cardTypeID
Having Sum([Transaction].amount) > 60000

--Task#6

Select [User].userId, [User].name, [User].phoneNum, [User].city,
[UserCard].cardNum, [Card].cardTypeID
From [User] Full Join [UserCard] on [User].userId = [UserCard].userID
Full Join [Card] on [UserCard].cardNum = [Card].cardNum
where [Card].expireDate < DATEADD(month, 3, GetDate()) 

--Task#7

Select [User].userId, [User].name from [User]
where [User].name in 
(
	Select [User].name 
	From [User] Full Join [UserCard] on [User].userId = [UserCard].userID
	Full Join [Card] on [UserCard].cardNum = [Card].cardNum
	Group by [User].name, [User].phoneNum
	Having sum([Card].balance) > 50000
)

--Task#8

Select C1.cardNum, C2.cardNum From [Card] as C1 join [Card] as C2
on C1.cardNum != C2.cardNum AND C1.cardNum < C2.cardNum
AND year(C1.expireDate) = year(C2.expireDate)

--Task#9

Select U1.Name, U2.Name From [User] as U1 join [User] as U2
on U1.Name != U2.Name AND U1.Name < U2.Name
AND SUBSTRING (U1.Name, 1, 1) = SUBSTRING (U2.Name, 1, 1)

--Task#10

Select [User].name, [User].userId 
From [User] Full Join [UserCard] on [User].userId = [UserCard].userID
Full Join [Card] on [UserCard].cardNum = [Card].cardNum
Full Join [CardType] on [CardType].cardTypeID = [Card].cardTypeID
Where [CardType].name = 'Debit' and [User].userId in 
(
	Select [User].userId 
	From [User] Full Join [UserCard] on [User].userId = [UserCard].userID
	Full Join [Card] on [UserCard].cardNum = [Card].cardNum
	Full Join [CardType] on [CardType].cardTypeID = [Card].cardTypeID
	Where [CardType].name = 'Credit'
)

--Task#11

Select [User].city, count([User].userId) as TotalUsers, Sum([Transaction].amount) as TotalAmount
From [User] Full Join [UserCard] on [User].userId = [UserCard].userID
Full Join [Transaction] on [Transaction].cardNum = [UserCard].cardNum
Group by [User].city