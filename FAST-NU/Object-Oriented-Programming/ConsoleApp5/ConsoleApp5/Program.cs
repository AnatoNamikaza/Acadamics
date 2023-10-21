using System;

namespace ConsoleApp5
{
    
    /*C# PROGRAM TO INPUT HOTEL RESERVATION DETAILS AND DISPALY USING CLASS */
    class Program
    {
        /* START OF MAIN METHOD */
        static void Main(string[] args)
        {

            /*LOCAL VARIABLE TO HOLD TEMPORARY DATA */
            string Fname, Lname, EmployeeID, Gender, RoomType, GuestType;
            DateTime StartDate;
            String whone, hphone, streetaddr, city, state, zip;
            GuestType = " ";
            Gender = "";

            /* HEADING MESSAHE */
            Console.Out.WriteLine("Welcome to the CPH Reservation System! ");
            Console.Out.WriteLine(""); // NEW LINE

            while (true) // LOOP INFINITE UNTIL USER STOPS
            {

                Console.Out.WriteLine("Add a new reservation ");

                /* INPUT DATA TO ALL LOCAL VARAIABLES */
                Console.Out.Write("Guest type : "); // MESSAGE TO SHOW INPUT GUEST TYPE
                GuestType = Console.ReadLine(); // READ TO VARAIABLE GUEST TYPE
                Console.Out.Write("First Name : "); // MESSAGE TO SHOW INPUT FIRST NAME
                Fname = Console.ReadLine(); // READ TO VAFRAIABLE FIRST NAME
                Console.Out.Write("Last Name : ");
                Lname = Console.ReadLine();

                while (Gender != "M" && Gender != "F") /// LOOP UNTIL USER ENTERS CORRECT INPUT FOR GENDER EITHER M/F
                {
                    Console.Out.Write("Gender (M/F): ");
                    Gender = Console.ReadLine();
                }

                

                Console.Out.Write("Room type : "); // MESSAGE TO SHOW INPUT GUEST TYPE
                GuestType = Console.ReadLine(); // READ TO VARAIABLE GUEST TYPE
                Console.Out.Write("Start Date : ");
                StartDate = DateTime.Parse(Console.ReadLine()); //CONEVERTING STRING TO DATE TYPE
                Console.Out.Write("Work Phone : ");
                whone = Console.ReadLine();
                Console.Out.Write("Home Phone : ");
                hphone = Console.ReadLine();
                Console.Out.Write("Street Address : ");
                streetaddr = Console.ReadLine();
                Console.Out.Write("City : ");
                city = Console.ReadLine();
                Console.Out.Write("State : ");
                state = Console.ReadLine();
                Console.Out.Write("Zip : ");
                zip = Console.ReadLine();

                Guest res = new Guest(); // CREATING INSTANCE OF EMPLOYE CLASS

                res.setData(Fname, Lname, Gender, StartDate, whone, hphone, streetaddr, city, state, zip); // CALLING SET METHOD OF EMPLOYE CLASS
                Console.Out.WriteLine(""); // NEW LINE

                res.PrintDetails(); // // CALLING PRINT METHOD OF EMPLOYE CLASS
                Console.Out.WriteLine(""); // NEW LINE

                String ch = "";

                while (ch != "Y" && ch != "N") /// LOOP UNTIL USER ENTERS CORRECT INPUT FOR GENDER EITHER Y/N
                {
                    Console.Out.Write("Do you want to quit (Y/N) : ");
                    ch = Console.ReadLine();

                    Console.Out.WriteLine(""); // NEW LINE
                }

                if (ch == "Y")
                    break; // OUTER WHILE LOOP WILL TERMINATE WHEN USER ENETER Y. SO NO MORE ASK TO UNPUT


            } // OUTER WHILE LOOP

            Console.Out.WriteLine(""); // NEW LINE

            Console.Out.Write("Thank you for using payroll system : "); // END MESSAGE
            Console.ReadLine(); // JUST FOR WAITING THE CONSOLE TO SEE FINAL MESSAGE

        }
    }

    /* GUEST CLASS DEFINITAION*/
    class Guest
    {
        /*CLASS DATA MEMBER*/
        string Fname;
        string Lname;
        string Gender;
        DateTime StartDate;
        PhoneNum phone;
        Address addr;

        /*CLASS MEMBER FUNCTION*/
        public void setData(string _fname, string _Lname, string _Gender, DateTime _StartDate, string _wphone,
        string _homephone, string _street, string _city, string _state, string _zip)
        {
            Fname = _fname;
            Lname = _Lname;
            Gender = _Gender;

            phone = new PhoneNum(); // CREATING INSTANCE OF PhoneNum CLASS

            /* INITIALIZE VALUES TO PhoneNum INSTANCE*/
            phone.HomePhone = _homephone;
            phone.WorkPhone = _wphone;

            addr = new Address(); // CREATING INSTANCE OF Address CLASS

            /* INITIALIZE VALUES TO ADDRESS INSTANCE*/
            addr.StreetAddress = _street;
            addr.City = _city;
            addr.State = _state;
            addr.Zip = _zip;

        }

        /* DISPLAY METHOD */
        public void PrintDetails()
        {
            String mstatus = "";
            int years = 0;
            String title = "";
            /* COUNTING NO OF YEARS */
            DateTime zeroTime = new DateTime(1, 1, 1);
            TimeSpan span = DateTime.Now - StartDate;

            years = (zeroTime + span).Year - 1;

            /* PRINT ALL DATA IN LINE */
            Console.WriteLine(title + " " + Fname + ", " + Lname + " " + mstatus + " " + addr.StreetAddress + ", " + addr.City + ", " + addr.State + " " + addr.Zip
            + ", (" + phone.HomePhone.Insert(3, ")") + ", (" + phone.WorkPhone.Insert(3, ")") + ", " + years + " years");
        
}

    }// END OF EMPLOYE CLASS
    /* ADDRESS CLASS DEFINITAION*/
    class Address
    {
        /*CLASS DATA MEMBER*/
        public string StreetAddress;
        public string City;
        public string State;
        public string Zip;

    } // END OF ADDRESS CLASS

    /* PHONENUM CLASS DEFINITAION*/
    class PhoneNum
    {
        /*CLASS DATA MEMBER*/
        public string HomePhone;
        public string WorkPhone;

    }
} // END OF MAIN CLASS