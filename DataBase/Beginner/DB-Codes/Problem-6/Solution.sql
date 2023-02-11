Create database customer-salesman;

use [customer-salesman]

create table salesman
(salesman_id int not null primary key,
sName varchar(50),
city varchar(50),
commission float);

create table customers
(customer_id int not null primary key,
cust_Name varchar(50),
city varchar(40),
grade int,
salesman_id int foreign key references salesman(salesman_id));

create table orders
(ord_no int,
purch_amt float,
order_date date,
customer_id int foreign key references customers(customer_id),
salesman_id int foreign key references salesman(salesman_id));

insert into salesman values 
(5001,'James Hoog','New York',0.15),
(5002,'Nail Knite','Pairs', 0.13),
(5005,'Pit Alex','London',0.11),
(5006,'Mc Lyon','Pairs',0.14),
(5007,'Paul Adam','San Jose',0.13),
(5003,'Lauson Hen','San Jose',0.12);

insert into customers values
(3002,'Nick Rimando','New York',100,5001),
(3007,'John Brad Davis','New York',200,5001),
(3005,'Graham Zusi','California',200,5002),
(3008,'Julian Green','London',300,5002),
(3004,'Fabian Johnson','Pairs',300,5006),
(3009,'Geoff Cameron','Berlin',100,5003),
(3003,'Jozy Altitor','Moscow',200,5007),
(3001,'John Brad Guzan','London', NULL,5005);

insert into orders values
(70001,150.5,'2012-10-05',3005, 5002),
(70009,270.65,'2011-09-10',3001, 5005),
(70002,65.26,'2014-10-05',3002, 5001),
(70004,110.5,'2011-8-17',3009, 5003),
(70007,948.5,'2012-9-10',3005, 5002),
(70005,2400.6,'2010-07-27',3007, 5001),
(70008,5760,'2013-9-10',3002, 5001),
(70010,1983.43,'2010-10-10',3004, 5006),
(70003,2480.4,'2013-10-10',3009, 5003),
(70012,250.45,'2010-6-27',3008, 5002),
(70011,75.29,'2014-08-17',3003, 5007),
(70013,3045.6,'2010-04-25',3002, 5001);


select *from customers
where city = 'New Yourk';

select *from customers
where cust_Name like '%John%' and (city = 'London' or city = 'Paris' or city = 'New Yourk');

select *from customers 
where (city = 'London' or city = 'New Yourk');

select *from orders
where (purch_amt>500);

select *from salesman
where(sName like '_a%');

select commission, commission+0.5 as UpdatedCommission
from salesman 
where city = 'San Jose';

select *from orders order by order_date desc;

select sName,LEFT(sName,CHARINDEX(' ',sName)) as firstname
from salesman;

select *from orders 
where (DATEPART(MONTH, order_date)=2);

--Task 10

select DATENAME(day,order_date) as Day_of_month, 
	DATENAME(WEEKDAY,order_date) as week_day,
	DATENAME(WEEK,order_date) as week,
	DATENAME(DAYOFYEAR,order_date) as day_of_year,
	DATENAME(month,order_date) as name_of_month,
	DATENAME(year,order_date) as year
from orders 
where DATEPART(month, order_date) = 10;

select order_date,purch_amt,purch_amt*3 as triple_amt 
from orders  
where (DATEPART(MONTH, order_date)=11); 

select *from customers
left join orders on orders.customer_id = customers.customer_id where( DATEPART(year, order_date) = 2011 or DATEPART(year, order_date) = 2013);

select *from salesman
where commission = (select MAX(commission) from salesman);

