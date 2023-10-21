a/*(Task-1)*/
create table Student (RollNum char(40),Name varchar(40),Gender varchar(40),Phone char(40));
create table Attendance (RollNum char(40),Date varchar(40),Status char(40),ClassVenue integer);
create table ClassVenue (ID integer,Building varchar(40),RoomNum integer,Teacher varchar(40));
create table Teacher (Name varchar(40),Designation varchar(40),Department varchar(40));

insert into [Student] ([RollNum], [Name], [Gender], [Phone])
values	('L164123', 'Ali Ahmad', 'Male', '0333-3333333'),('L164124', 'Rafia Ahmed', 'Female', '0333-3456789'),('L164125', 'Basit Junaid', 'Male', '0345-3243567')
go

insert into [Attendance] ([RollNum], [Date], [Status], [ClassVenue])
values	('L164123', '2-22-2016', 'P', 2),('L164124', '2-23-2016', 'A', 1),('L164125', '3-4-2016', 'P', 2)
go

insert into [ClassVenue] ([ID], [Building], [RoomNum], [Teacher])
values	(1, 'CS', 2, 'Sarim Baig'),(2, 'Civil', 7, 'Bismillah Jan')
go

insert into [Teacher] ([Name], [Designation], [Department])
values	('Sarim Baig', 'Assistant Prof.', 'Computer Science'),('Bismillah Jan', 'Lecturer', 'Civil Eng.'),('Kashif zafar', 'Professor', 'Electrical Eng.')
go

/*(Task-2)*/
alter table Student add constraint 
Prime_A primary key (RollNum)
alter table Attendance add constraint 
Prime_B primary key (RollNum)
alter table ClassVenue add constraint 
Prime_C primary key (ID)
alter table Teacher add constraint 
Prime_D primary key (Name)

/*(Task-3)*/
alter table Attendance
add constraint Foreign1 foreign key (RollNum) 
references Student(RollNum) on update cascade on delete set null


alter table Attendance
add constraint Foreign2 foreign key (ClassVenue) 
references ClassVenue(ID) on update cascade on delete set null


alter table ClassVenue
add constraint Foreign3 foreign key (Teacher) 
references Teacher(Name) on update cascade on delete set null


/*(Task-4)*/
alter table Student add Warning_Count integer
alter table Student drop column [Phone]

/*(Task-5.1)*/
insert into [Student] ([RollNum], [Name], [Gender], [Warning_Count])
values ('L162334', 'Fozan Shahid', 'Male', 3.2)
go
/*Valid Query*/

/*(Task-5.2)*/
insert into [ClassVenue] ([ID], [Building], [RoomNum], [Teacher])
values	(3, 'CS', 5, 'Ali')
go
/*Invalid Query, we must first add this teacher in teacher table and then run this.*/

/*(Task-5.3)*/
update Teacher
set Name='Dr. Kashif Zafar'
where Name='Kashif zafar'
/*Valid Query*/

/*(Task-5.4)*/
delete from Student
where RollNum='L162334'
/*Valid Query*/

/*(Task-5.5)*/
delete from Student
where RollNum='L164123'
/*Invalid Query, we must first delete all entries in Attendance table with L164123 value in rollno and then run this.*/

/*(Task-5.6)*/
delete from Attendance
where RollNum='L164124' and Status='A'
/*Valid Query*/

/*(Task-6.1)*/
alter table Teacher 
add constraint UniqueElement unique (Name)

/*(Task-6.2)*/
alter table Student 
add check (Gender='Male' or Gender='Female')

/*(Task-6.3)*/
alter table Attendance 
add check(Status='P' or Status='A')