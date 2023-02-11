create procedure std_registration
(
@input_rn int,
@input_cn int,
@input_sem varchar(30)
)
as begin
begin transaction
save transaction savepoint;

if @input_rn in (select student_CGPA.rollno from (select Registration.RollNumber as rollno,(sum(Courses.CreditHours * Registration.GPA)/sum (Courses.CreditHours)) as CGPA
from Registration join Courses on Registration.CourseID = Courses.CourseID group by RollNumber)as student_CGPA where CGPA < 2.5 and @input_rn = student_CGPA.rollno)
begin 
Print 'Student with Roll Number '+CAST(@input_rn as varchar(10))+' can only enroll in subjects that he can improve. (0_0)'
rollback transaction savepoint;
end
else
insert into Registration 
values 
(
@input_sem,
@input_rn,
@input_cn,
(select Top(1) Courses_Semester.Section from Courses_Semester 
where Courses_Semester.CourseID = @input_cn and Courses_Semester.AvailableSeats > 0),
0
)
Update Courses_Semester
set Courses_Semester.AvailableSeats -= 1
where Courses_Semester.Section = (select Top(1) Courses_Semester.Section from Courses_Semester 
where Courses_Semester.CourseID = @input_cn and Courses_Semester.AvailableSeats > 0)
commit transaction
end

exec std_registration
@input_rn = 2,
@input_cn = 10,
@input_sem = 'Spring2017'
go

select * from Students
select * from Courses
select * from Courses_Semester
select * from Registration