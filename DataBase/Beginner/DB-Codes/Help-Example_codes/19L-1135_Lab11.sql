--Task#1
CREATE TRIGGER Update_Warning
ON Semester
after Update, Insert
as
begin
	if (select Status from inserted) = 'Complete'
	begin
		declare @sem varchar(20) = (select Semester from inserted)
		Update Students
		set Students.WarningCount += 1
		where Students.RollNo in (
			select Registration.RollNumber
			From Registration join Courses 
			on	Registration.CourseID = Courses.CourseID
			where Registration.Semester = @sem
			group by RollNumber
			Having Count(Registration.CourseID) >= 2
			And 
			(
				sum(Courses.CreditHours * Registration.GPA)
				/sum (Courses.CreditHours) < 2
			)
		)
	end
end


update Semester 
set Semester.status = 'Complete'
where Semester.Semester ='Fall2016'

select * from Students

insert into Registration values ('Fall2016', 6, 10,'D', 0 )
insert into Registration values ('Fall2016', 1, 10,'D', 0 )

Delete from Registration 
where Semester = 'Fall2016' And CourseID = 10

update Students 
set Students.WarningCount = 0
where Students.RollNo =1

--||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

--Task#2
ALTER TABLE Semester
ADD Average_gpa float NuLL,
fail_count int NuLL,
pass_count int NuLL,
gold_medalist int NuLL,
silver_medalist int NuLL,
bronze_medalist int NuLL;

select * from Semester

CREATE TRIGGER Update_Warning
ON Semester
after Update, Insert
as
begin
	if (select Status from inserted) = 'Complete'
	begin
		declare @sem varchar(20) = (select Semester from inserted)
	
		Update Students
		set Students.WarningCount += 1
		where Students.RollNo in (
			select Registration.RollNumber
			From Registration join Courses 
			on	Registration.CourseID = Courses.CourseID
			where Registration.Semester = @sem
			group by RollNumber
			Having Count(Registration.CourseID) >= 2
			And 
			(
				sum(Courses.CreditHours * Registration.GPA)
				/sum (Courses.CreditHours) < 2
			)
		)

		declare @f_stds int =
		(
			select count(T1.R_num)
			from
			(
				select Registration.RollNumber as R_num
				From Registration join Courses 
				on	Registration.CourseID = Courses.CourseID
				where Registration.Semester = @sem
				group by RollNumber
				Having Count(Registration.CourseID) >= 2
				And 
				(
					sum(Courses.CreditHours * Registration.GPA)
					/sum (Courses.CreditHours) < 2
				)
			) as T1
		),

		@p_stds int =
		(
			select count(T1.R_num)
			from
			(
				select Registration.RollNumber as R_num
				From Registration join Courses 
				on	Registration.CourseID = Courses.CourseID
				where Registration.Semester = @sem
				group by RollNumber
				Having Count(Registration.CourseID) >= 2
				And 
				(
					sum(Courses.CreditHours * Registration.GPA)
					/sum (Courses.CreditHours) >= 2
				)
			) as T1
		),

		@g_stds int =
		(
			select count(T1.R_num)
			from
			(
				select Registration.RollNumber as R_num
				From Registration join Courses 
				on	Registration.CourseID = Courses.CourseID
				where Registration.Semester = @sem
				group by RollNumber
				Having Count(Registration.CourseID) >= 2
				And 
				(
					sum(Courses.CreditHours * Registration.GPA)
					/sum (Courses.CreditHours) >= 3.9
				)
			) as T1
		),

		@s_stds int =
		(
			select count(T1.R_num)
			from
			(
				select Registration.RollNumber as R_num
				From Registration join Courses 
				on	Registration.CourseID = Courses.CourseID
				where Registration.Semester = @sem
				group by RollNumber
				Having Count(Registration.CourseID) >= 2
				And 
				(
					sum(Courses.CreditHours * Registration.GPA)
					/sum (Courses.CreditHours) between 3.5 And 3.8
				)
			) as T1
		),

		@b_stds int =
		(
			select count(T1.R_num)
			from
			(
				select Registration.RollNumber as R_num
				From Registration join Courses 
				on	Registration.CourseID = Courses.CourseID
				where Registration.Semester = @sem
				group by RollNumber
				Having Count(Registration.CourseID) >= 2
				And 
				(
					sum(Courses.CreditHours * Registration.GPA)
					/sum (Courses.CreditHours) between 3.0 And 3.4
				)
			) as T1
		),

		@avg_gpa float =
		(
			(
				select sum (T1.CGPAs)
				from
				(
					select	
					sum(Courses.CreditHours * Registration.GPA)
					/sum (Courses.CreditHours) as CGPAs
					From Registration join Courses 
					on	Registration.CourseID = Courses.CourseID
					where Registration.Semester = @sem
					group by RollNumber
					Having Count(Registration.CourseID) >= 2
				) as T1
			)
			/
			CAST(
			(
				select count(T1.R_num)
				from
				(
					select Registration.RollNumber as R_num
					From Registration join Courses 
					on	Registration.CourseID = Courses.CourseID
					where Registration.Semester = @sem
					group by RollNumber
					Having Count(Registration.CourseID) >= 2
				) as T1
			) 
			as float
			)
		)

		--select @avg_gpa,@f_stds,@p_stds,@g_stds,@s_stds,@b_stds

		Update Semester
		set Semester.Average_gpa = @avg_gpa,
		Semester.fail_count = @f_stds,
		Semester.pass_count = @p_stds,
		Semester.gold_medalist = @g_stds,
		Semester.silver_medalist = @s_stds,
		Semester.bronze_medalist = @b_stds
		where Semester.Semester = @sem
	end
end

update Semester 
set Semester.status = 'Complete'
where Semester.Semester ='Fall2016'
select * from Registration

select * from Students
select * from Semester

insert into Registration values ('Fall2016', 6, 10,'D', 0 )
insert into Registration values ('Fall2016', 1, 10,'D', 4 )

Delete from Registration 
where Semester = 'Fall2016' And CourseID = 10

update Students 
set Students.WarningCount = 1
where Students.RollNo =6

--||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

--Task#3
Create Procedure Registeration_checker
@input_Roll_no int,
@input_Course_id int,
@input_Sem varchar(20)
as begin 
	
	declare @violation_count int = 0,
	@pre int = 0

	if (select Courses.PrerequiteCourseID from Courses where CourseID = @input_Course_id ) Is not NULL
	begin
		set @pre = (select Courses.PrerequiteCourseID from Courses where CourseID = @input_Course_id )
	end
	
	if @pre > 0
	begin
		if (select Registration.GPA from Registration where CourseID = @pre and RollNumber = @input_Roll_no ) < 2 
		begin
			Print 'student has not completed prerequisite of the course in which he wants to register.'
			set @violation_count +=1
		end
	end

	if (select Students.WarningCount from Students where Students.RollNo = @input_Roll_no) > 0 
	begin
		Print 'Warning count of student is not zero.'
		set @violation_count +=1
	end

	if (
		select Top(1) Courses_Semester.Section from Courses_Semester 
		where Courses_Semester.CourseID = @input_Course_id and Courses_Semester.AvailableSeats > 0
	) is Null
	begin
		Print 'seat are not available in any section of that course.'
		set @violation_count +=1
	end

	if (
		select Distinct Courses_Semester.Department from Courses_Semester 
		where Courses_Semester.CourseID = @input_Course_id 
		and Courses_Semester.AvailableSeats > 0
	) != (
		select Students.Department from Students 
		where Students.RollNo = @input_Roll_no
	) 
	begin
		Print 'The course is not being offered in that semester by the same department to which student belong to.'
		set @violation_count +=1
	end

	if @violation_count > 0
	begin
		rollback
	end

	insert into Registration 
	values 
	(
	@input_Sem,
	@input_Roll_no,
	@input_Course_id,
	(select Top(1) Courses_Semester.Section from Courses_Semester 
	where Courses_Semester.CourseID = @input_Course_id and Courses_Semester.AvailableSeats > 0),
	(select Registration.GPA from Registration where CourseID = @pre and RollNumber = @input_Roll_no )
	)

	Update Courses_Semester
	set Courses_Semester.AvailableSeats -= 1
	where Courses_Semester.Section = (select Top(1) Courses_Semester.Section from Courses_Semester 
	where Courses_Semester.CourseID = @input_Course_id and Courses_Semester.AvailableSeats > 0)

	insert into ChallanForm 
	values 
	(
	@input_Sem,
	@input_Roll_no,
	( 7000 * (select Courses.CreditHours from Courses where CourseID = @input_Course_id)),
	'Paid'
	)

	declare @c varchar(20) = (
		select Courses.CourseName from Courses 
		where CourseID = @input_Course_id
	),
	@s varchar(2) = (
		select Top(1) Courses_Semester.Section from Courses_Semester 
		where Courses_Semester.CourseID = @input_Course_id 
		and Courses_Semester.AvailableSeats > 0
	)

	Print 'Registation to '+@c+' Section '+@s+' Successful (^_^)'
end

exec Registeration_checker
@input_Roll_no = 1,
@input_Course_id = 10,
@input_Sem = 'Spring2017'
go

select * from Registration
select * from Courses_Semester
select * from ChallanForm

--Note:
--The semester has also being taken as input parameter for the insertion of attribute 'Semester' 
--in all the tables.