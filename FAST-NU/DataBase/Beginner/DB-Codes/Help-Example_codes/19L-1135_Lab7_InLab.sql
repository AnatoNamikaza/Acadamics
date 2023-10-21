----Task#1
--CREATE TRIGGER delstudent
--ON Students
--instead of DELETE
--AS
--begin
--  print'You don’t have the permission to delete the student'
--end

--DELETE FROM Students WHERE warningcount = 2
--select*from students


--INSERT [dbo].[Students] ([RollNo], [Name], [WarningCount], [Department]) VALUES (N'7', N'Zainab', 2, N'CS')


----Task#2
--CREATE TRIGGER insCorse
--ON Courses
--instead of Insert
--AS
--begin
--  print'You don’t have the permission to Insert a new Course'
--end

--INSERT [dbo].[Courses] ([CourseID], [CourseName], [PrerequiteCourseID],CreditHours) VALUES (50, N'Basic', NULL,5)

--select*from Courses


----Task#3
--Create Table Notify
--(
--NotifictionID int, 
--StudentID int,
--Notification Varchar(20)
--)

--create trigger reg_course
--on Registration
--instead of insert
--as begin
--declare @rollno int, @Course int, @PCourse int, @cleared int, @GPA int,
--@Semester varchar(30),@Section varchar(2)
--select @rollno = inserted.RollNumber, @Course = CourseID, @GPA = GPA, @Semester=Semester,@Section=Section
--from inserted 

--select @PCourse = PrerequiteCourseID from Courses where CourseID = @Course

--select @cleared = GPA from Registration where CourseID=@PCourse 
--and RollNumber=@rollno

--if  (@GPA<2) or (@cleared<2)
--	begin
--		Insert into Notify Values (1,@rollno,N'Not Successful')
--	end
--else
--	begin
--		INSERT [dbo].[Registration] VALUES (@Semester,@rollno, @Course, @Section,@GPA)
--		Insert into Notify Values (1,@rollno,N'Successful')
--	end
--end

--INSERT [dbo].[Registration] ([Semester], [RollNumber], [CourseID],[Section],GPA) VALUES (N'Spring2017', N'4', 40, N'D',7)

--select * from Notify

--select * from Registration

--delete from Notify where StudentID = 4
--delete from Registration where RollNumber = 4

------Task#4
--create trigger enrol_course
--on Registration
--instead of insert
--as begin
--declare @rollno int
--select @rollno = RollNumber from inserted 
--if @rollno in (select ChallanForm.RollNumber from ChallanForm 
--	where ChallanForm.Status='Pending' and ChallanForm.TotalDues>=20000)
--	begin
--	print'Due not cleared'
--	end
--end

--INSERT [dbo].[Registration] ([Semester], [RollNumber], [CourseID], [Section],GPA) VALUES (N'Spring2017', N'4', 40, N'D',1)


--select* from Registration


----Task#5
--create trigger del_sem_course
--on Courses_Semester
--instead of delete
--as begin
--declare @seats int
--select @seats = AvailableSeats from deleted
--if(@seats < 10)
--	begin
--	print'Not Possible'
--	end
--end

--INSERT [dbo].[Courses_Semester] ([InstructorID], [CourseID], [Semester], [Section], [AvailableSeats], [Department]) VALUES (100, 10, N'Spring2017', N'A', 9, N'CS')

--delete from Courses_Semester where InstructorId = 100 and AvailableSeats = 9

--select* from Courses_Semester

----Task#6
--CREATE TRIGGER drop_alter_safe 
--ON DATABASE
--For Drop_Table, Alter_Table 
--AS 
--begin
--   PRINT 'You must disable Trigger "drop_alter_safe" to drop or alter a table in database.' 
--	RollBack
--end

--ALTER TABLE Instructors
--ADD test int;

--select*from Instructors
