--script file empCustDbScript.sql

--Task#1
--select *from Customer
--where (city = 'London' or city = 'Marseille');

--Task#2
--SELECT * FROM Customer
--WHERE Country NOT IN ('Germany', 'France', 'Italy')

--Task#3
--select count(*) as 'Number of Customers' from Customer
--where Country = 'UK' ;

--Task#4
--select FirstName, LastName, Country, Phone From Customer
--where Phone like '%171%'

--Task#5
--select FirstName, LastName, Country, Phone From Customer
--where (Phone like '%7_' or Phone like '%8_') and Country IN ('Germany', 'France', 'UK', 'USA')

--Task#6
--select Top 5* From [Order]
--ORDER BY  TotalAmount desc

--Task#7
--select * From [Order]
--where (TotalAmount between 200 and 1000) and (TotalAmount Not in (440,670.80))

--Task#8
--select OrderDate,OrderNumber,TotalAmount, ((TotalAmount/7000)*100) as Achieved,(100-((TotalAmount/7000)*100)) as Unachieved From [order]
--where ((TotalAmount/7000)*100)> 50
--Order by TotalAmount desc

--Task#9
--select Customer.FirstName+' '+Customer.LastName as FullName, Customer.Id as PersonID, Customer.Country as PersonCountry, 'Customer' as PersonType From Customer
--where Customer.Country='UK'
--Union select Supplier.ContactName as FullName, Supplier.Id as PersonID, Supplier.Country as PersonCountry, 'Supplier' as PersonType from Supplier
--where Supplier.Country='UK'

--Task#10
--select * From Product
--where ( SupplierId > 10) and ( UnitPrice between 30 and 100)

