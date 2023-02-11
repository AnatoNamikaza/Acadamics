----Task#1
--Create View creators_trainers
--as
--select Distinct creators.c_id, creators.first_name, creators.email
--From creators join art_piece_details
--on creators.c_id = art_piece_details.creator_id
--join piece_type
--on piece_type.type_id = art_piece_details.type_id
--where creators.creator_Trainer_id is not null
--and piece_type.type_name = 'scenery'
--go 

--select * from creators_trainers

----Task#2
--Create Procedure id_checker
--@input_id int,
--@result int output
--as begin 
--	if @input_id in (select c_id from creators_trainers ) 
--		begin
--			set @result = 1
--		end
--	else
--		begin
--			set @result = 0
--		end
--end

--declare @found int = 0 

--exec id_checker
--@input_id = 4,
--@result = @found output
--select @found;
--go

--Task#3
--Create View art_piece_sum
--as
--select art_id, total_sales from(
--	select art_piece_details.art_id, 0 as total_sales
--	From art_piece_details
--	where art_piece_details.art_id not in (
--		select art_piece_details.art_id	From art_piece_details join sale on sale.art_id = art_piece_details.art_id
--		join payment_mode on sale.payment_mode_id = payment_mode.p_id where payment_mode.payment_mode = 'cash')
--	union all
--	select art_piece_details.art_id, count(art_piece_details.art_id) as total_sales
--	From art_piece_details join sale
--	on sale.art_id = art_piece_details.art_id
--	join payment_mode
--	on sale.payment_mode_id = payment_mode.p_id
--	where payment_mode.payment_mode = 'cash'
--	group by art_piece_details.art_id) as p
--go 

--select * from art_piece_sum

----Task#4
--create trigger sales_inserter
--on sale
--instead of insert
--as begin
--declare @amont int = (select inserted.quantity from inserted),
--@id int = (select inserted.art_id from inserted),
--@s_id int = (select inserted.s_id from inserted),
--@date varchar(11) = (select inserted.date_of_sale from inserted),
--@p_id int = (select inserted.payment_mode_id from inserted)

--	if @amont > (select art_pieces.quantity_available from art_pieces where art_id=@id) 
--		begin
--			print'required amount not available.'
--			RollBack
--		end
--	else
--		begin
--			update art_pieces
--			set quantity_available = quantity_available - @amont
--			insert into sale values (@s_id,@id,@date,@amont,@p_id)
--		end
--end

--insert into sale values (12,4,'2030-01-04',1,2)

----Task#5
--create trigger creater_inserter
--on creators
--after insert
--as begin
--declare @id int = (select inserted.c_id from inserted),
--@s_id int = (select inserted.creator_Trainer_id from inserted)
--	if @id =@s_id
--		begin
--			print'same id not allowed.'
--			RollBack
--		end
--end

--insert into creators values (21,'Axlia','Butt','jranwala', '030094454','asdfa@gmail.com',4)

--select * from creators
