--Q1
create function TSum(@pid int)  
returns int   
as begin declare @s int = (select sum(T1.total_s)
				from (select (product.Price*OrderItem.quantity) as
				total_s from product join OrderItem
				on product.productId = @pid
				and product.productID = OrderItem.productID) as T1) 
    return @s;  
end; 

select dbo.TSum(4)

--Q2
create function ic(@Cid int)
returns table as return	(select product.productID, product.productName,
						product.Price, OrderItem.OrderID, OrderItem.quantity
						from product join OrderItem	on 
						product.productID = OrderItem.productID
						join [Order] on [Order].OrderID = OrderItem.OrderID 
						where [Order].CustomerID=@Cid)

select * from dbo.ic(2) 

--Q3
select product.productID, product.productName, dbo.TSum(productID) from product