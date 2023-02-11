
--Task#1
select *from guest
where guestaddress like '%London%'
order by guestname desc

--Task#2
select hotelname, count(roomno) as total_rooms from hotel join room
on hotel.hotelno = room.hotelno
group by hotelname

--Task#3
select hotelname, avg(price) as avg_price from hotel join room
on hotel.hotelno = room.hotelno
where city = 'London'
group by hotelname

--Task#4
select hotelno, roomno, type, price from room
where (type='double' and price in (select max(price) from room where type = 'double'))
or (type='single' and price in (select max(price) from room where type = 'single'))
or (type='family' and price in (select max(price) from room where type = 'family'))

--Task#5
select distinct hotelname, city, type from hotel join room
on hotel.hotelno = room.hotelno

--Task#6
select hotelname, city from hotel join booking on hotel.hotelno=booking.hotelno
join (select *from guest
where guestaddress like '%London%') as table1 on table1.guestno=booking.guestno 

--Task#7
select hotelname, city, count(guestno) from hotel join booking on hotel.hotelno=booking.hotelno
group by hotelname,city order by count(guestno) desc

--Task#8
select * from guest left join booking on guest.guestno=booking.guestno
where booking.dateto is null

--Task#9
select hotelname, roomno, guestno from hotel join booking on hotel.hotelno=booking.hotelno
where year(datefrom) in (2001,2002)

--Task#10
select * from hotel
where hotelno not in (select hotelno from booking)

--Task#11
select hotel.hotelno, hotelname,roomno, 'family', price from hotel  join  room on hotel.hotelno = room.hotelno
where type='family'
union
select hotel.hotelno, hotelname,null, null, null from hotel join room on hotel.hotelno = room.hotelno
where hotel.hotelno not in (
select hotel.hotelno from hotel join room on hotel.hotelno = room.hotelno
where type='family')

--Task#12
select Distinct count(guestname) as totalguest from guest left join booking on guest.guestno=booking.guestno
where year(booking.dateto) = 2015 and month(booking.dateto) = 4


