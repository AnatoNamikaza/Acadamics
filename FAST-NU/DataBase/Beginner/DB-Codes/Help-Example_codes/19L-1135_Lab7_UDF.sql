----Task#1
--CREATE FUNCTION Total_Sale(@ProductID int)  
--RETURNS int   
--AS   
--BEGIN  
--    DECLARE @ret int;  
--    SELECT @ret = SUM(p.Sales)
--    FROM (
--	select (Product.Price*OrderItem.quantity) as Sales from Product join OrderItem
--	on Product.ProductID = OrderItem.ProductID and Product.ProductId=@ProductID
--	) as p     
--	IF (@ret IS NULL)   
--        SET @ret = 0;  
--    RETURN @ret;  
--END; 

--SELECT dbo.Total_Sale(1) as Total_Sales

----Task#2
--CREATE FUNCTION All_Info(@CustomerId int)
--RETURNS TABLE
--AS
--RETURN
--(SELECT Product.ProductID, 
--        Product.ProductName, 
--        Product.Price,
--		OrderItem.OrderID,
--		OrderItem.quantity
--	FROM Product join OrderItem
--	on Product.ProductID = OrderItem.ProductID
--	join [Order] on [Order].OrderID=OrderItem.OrderID
--	where [Order].CustomerID=@CustomerId
--)

--SELECT * from dbo.All_Info(2) 

----Task#3
--SELECT ProductID,ProductName, dbo.Total_Sale(ProductID) as Total_Sales from Product
