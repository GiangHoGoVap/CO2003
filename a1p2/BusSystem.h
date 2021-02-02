/* Note: 
    * You change anything in this answer 
    * such that your implementation must have BusSystem class with method query.
    * This query method should return the output of each instruction
*/
#include <cstring>

enum Options
{
    MAXIMUM_TRIP,
    INSERT_TRIP,
    DELETE_TRIP,
    CASE_START,
    CASE_END,
    LICENSE_PLATE_START,
    LICENSE_PLATE_END,
    WRONG
};

Options resolveOptions(string &requestS, string &restS)
{
    if (requestS == "SQ")
        return MAXIMUM_TRIP;
    else if (requestS == "INS")
        return INSERT_TRIP;
    else if (requestS == "DEL")
        return DELETE_TRIP;
    else if (requestS == "CS")
        return CASE_START;
    else if (requestS == "CE")
        return CASE_END;
    else if (requestS == "GS")
        return LICENSE_PLATE_START;
    else if (requestS == "GE")
        return LICENSE_PLATE_END;
    else
        return WRONG;
}

bool is_Number(string s)
{
    char *ptr_kiemtra = new char[s.length() + 1];
    strcpy(ptr_kiemtra, s.c_str());
    ptr_kiemtra[s.length()] = '\0';
    char *temp = ptr_kiemtra;
    while (*ptr_kiemtra != '\0')
    {
        if (isdigit(*ptr_kiemtra) == false)
        {
            delete[] temp;
            return false;
        }
        ptr_kiemtra++;
    }
    delete[] temp;
    return true;
}

class BusSystem
{
public:
    class Chuyen;
    class Tuyen;

private:
    Tuyen *t_head;
    int NumberOfTrips;
    bool firstTime;

public:
    class Chuyen
    {
    private:
        string CODE, LP;
        bool CASE;
        int TIME_A, TIME_B;
        Chuyen *c_next;
        friend class BusSystem;
        friend class Tuyen;

    public:
        Chuyen()
        {
            this->CODE = "";
            this->LP = "";
            this->CASE = 0;
            this->TIME_A = -1;
            this->TIME_B = -1;
            this->c_next = NULL;
        }
    };

    class Tuyen
    {
    private:
        string TuyenSo;
        int NumberOfTripsNow;
        int NumberOfTrips;
        Tuyen *t_next;
        Chuyen *c_head;
        friend class BusSystem;

    public:
        Tuyen()
        {
            this->TuyenSo = "";
            this->NumberOfTripsNow = 0;
            this->t_next = NULL;
            this->c_head = NULL;
        }
        ~Tuyen()
        {
            Chuyen *ptr = this->c_head;
            Chuyen *prev = ptr;
            while (ptr != NULL)
            {
                ptr = ptr->c_next;
                delete prev;
                prev = ptr;
            }
            this->c_head = NULL;
            this->NumberOfTripsNow = 0;
        }
        int insertVaoTuyen(Chuyen *obj)
        {

            if (this->NumberOfTripsNow >= NumberOfTrips)
            {
                return -1;
            }
            Chuyen *ptr = this->c_head;
            if (c_head == NULL)
            {
                c_head = obj;
                NumberOfTripsNow++;
                return NumberOfTripsNow;
            }
            else
            {
                while (ptr != NULL)
                {
                    if (ptr->CASE == obj->CASE && ptr->TIME_A == obj->TIME_A)
                        return -1;
                    if (ptr->LP == obj->LP && obj->TIME_A <= ptr->TIME_B && obj->TIME_B >= ptr->TIME_B)
                        return -1;
                    if (obj->TIME_A == ptr->TIME_A && obj->CODE == ptr->CODE && obj->CASE == ptr->CASE)
                        return -1;
                    if (ptr->c_next == NULL)
                    {
                        break;
                    }
                    ptr = ptr->c_next;
                }
                obj->c_next = ptr->c_next;
                ptr->c_next = obj;
                NumberOfTripsNow++;
                return NumberOfTripsNow;
            }
        }
    };

public:
    BusSystem()
    {
        this->t_head = NULL;
        this->NumberOfTrips = 0;
        firstTime = true;
    }
    ~BusSystem()
    {
        Tuyen *ptr = this->t_head;
        Tuyen *prev = ptr;
        while (ptr != NULL)
        {
            ptr = ptr->t_next;
            delete prev;
            prev = ptr;
        }
    }
    string query(string);
    int SQ_1(string);
    int INS_2(string);
    int DEL_3(string);
    int CS_4(string);
    int CE_5(string);
    string GS_6(string);
    string GE_7(string);
};

string BusSystem::query(string instruction)
{
    //char* pRequest = new char[instruction.length() + 1];
    //std::strcpy (pRequest, instruction.c_str());
    const char *pRequest = instruction.c_str();
    string requestString = "";
    string requestIN4 = "";
    if (*pRequest == ' ')
    {
        return "-1";
    }
    while (*pRequest != ' ' && *pRequest != '\0')
    {
        requestString += *(pRequest++);
    }
    if (*pRequest != '\0')
    {
        requestIN4 = ++pRequest;
    }

    switch (resolveOptions(requestString, requestIN4))
    {
    case MAXIMUM_TRIP:
        return to_string(SQ_1(requestIN4));
        break;
    case INSERT_TRIP:
        return to_string(INS_2(requestIN4));
        break;
    case DELETE_TRIP:
        return to_string(DEL_3(requestIN4));
        break;
    case CASE_START:
        return to_string(CS_4(requestIN4));
        break;
    case CASE_END:
        return to_string(CE_5(requestIN4));
        break;
    case LICENSE_PLATE_START:
        return GS_6(requestIN4);
        break;
    case LICENSE_PLATE_END:
        return GE_7(requestIN4);
        break;
    default:
        return "-1";
        break;
    }
}

int BusSystem::SQ_1(string str)
{
    const char *kiemtra = str.c_str();
    //kiem tra o middle
    if (*kiemtra == ' ')
        return -1;
    //kiem tra o cuoi
    while (*kiemtra != ' ' && *kiemtra != '\0')
    {
        if (*(kiemtra++) == ' ')
            return -1;
    }
    if (firstTime)
    {
        if (is_Number(str) == false)
            return -1;
        NumberOfTrips = stoi(str);
        firstTime = false;
        return 1;
    }
    else
        return -1;
}

int BusSystem::INS_2(string str)
{
    char *pR = new char[str.length() + 1];
    std::strcpy(pR, str.c_str());
    if (*pR == ' ')
    {
        return -1;
    }
    char *temp = pR;
    int counter = 0;
    while (*pR != '\0')
    {
        if (*pR == ' ')
            counter++;
        pR++;
    }
    if (counter > 4)
    {
        return -1;
    }
    Chuyen *obj = new Chuyen;
    pR = temp;
    // CODE
    string newstr = "";
    while (*pR != ' ')
    {
        newstr += *(pR++);
    }
    pR++;
    if (*pR == ' ')
    {
        delete obj;
        return -1;
    }
    obj->CODE = newstr;
    // LP
    newstr = "";
    while (*pR != ' ')
    {
        newstr += *(pR++);
    }
    pR++;
    if (*pR == ' ')
    {
        delete obj;
        return -1;
    }
    obj->LP = newstr;
    // CASE
    if (counter == 4)
    {
        newstr = "";
        while (*pR != ' ')
        {
            newstr += *(pR++);
        }
        pR++;
        if (*pR == ' ' || is_Number(newstr) == false || *pR == '\0')
        {
            delete obj;
            return -1;
        }
        obj->CASE = stoi(newstr);
        if (obj->CASE != 0 && obj->CASE != 1)
        {
            delete obj;
            return -1;
        }
    }
    else
    {
        obj->CASE = 0;
    }
    // TIME_A
    newstr = "";
    while (*pR != ' ')
    {
        newstr += *(pR++);
    }
    pR++;
    if (*pR == ' ' || is_Number(newstr) == false || *pR == '\0')
    {
        delete obj;
        return -1;
    }
    obj->TIME_A = stoi(newstr);
    // TIME_B
    newstr = "";
    while (*pR != '\0')
    {
        newstr += *(pR++);
        if (*pR == ' ')
            return -1;
    }
    if (is_Number(newstr) == false)
    {
        delete obj;
        return -1;
    }
    obj->TIME_B = stoi(newstr);
    delete[] temp;
    //---------Xong tách chuỗi----------

    Tuyen *ptr = this->t_head;
    bool matching = false;
    // Nếu chưa có tuyến nào trong hệ thống
    if (t_head == NULL)
    {
        Tuyen *temp = new Tuyen;
        temp->TuyenSo = obj->CODE;
        temp->NumberOfTrips = NumberOfTrips;
        this->t_head = temp;
        ptr = temp;
    }
    // Tìm tuyến xem đã có chưa
    while (ptr != NULL)
    {
        if (ptr->TuyenSo == obj->CODE)
        {
            matching = true;
            break;
        }
        if (ptr->t_next == NULL)
        {
            break;
        }
        ptr = ptr->t_next;
    }
    if (matching == false && t_head != NULL)
    {
        Tuyen *temp = new Tuyen;
        temp->TuyenSo = obj->CODE;
        temp->NumberOfTrips = NumberOfTrips;
        ptr->t_next = temp;
        ptr = temp;
    }

    // insert chuyen vao tuyen
    return ptr->insertVaoTuyen(obj);
}

int BusSystem::DEL_3(string str)
{
    char *pR = new char[str.length() + 1];
    std::strcpy(pR, str.c_str());
    if (*pR == ' ')
    {
        return -1;
    }
    char *temp = pR;
    int counter = 0;
    while (*pR != '\0')
    {
        if (*pR == ' ')
            counter++;
        pR++;
    }
    if (counter > 2)
    {
        return -1;
    }
    Chuyen *obj = new Chuyen;
    pR = temp;
    if (counter == 0)
    {
        // CODE
        string newstr = "";
        while (*pR != '\0')
        {
            newstr += *(pR++);
        }
        pR++;
        obj->CODE = newstr;
    }
    if (counter == 1)
    {
        // CODE
        string newstr = "";
        while (*pR != ' ')
        {
            newstr += *(pR++);
        }
        pR++;
        if (*pR == ' ' || *pR == '\0')
        {
            delete obj;
            return -1;
        }
        obj->CODE = newstr;

        newstr = "";
        while (*pR != '\0')
        {
            newstr += *(pR++);
        }
        //pR++;
        if (is_Number(newstr) == false)
        {
            delete obj;
            return -1;
        }
        obj->TIME_A = stoi(newstr);
    }
    if (counter == 2)
    {
        // CODE
        string newstr = "";
        while (*pR != ' ')
        {
            newstr += *(pR++);
        }
        pR++;
        if (*pR == ' ' || *pR == '\0')
        {
            delete obj;
            return -1;
        }
        obj->CODE = newstr;

        newstr = "";
        while (*pR != ' ')
        {
            newstr += *(pR++);
        }
        pR++;
        if (*pR == ' ' || is_Number(newstr) == false || *pR == '\0')
        {
            delete obj;
            return -1;
        }
        obj->TIME_A = stoi(newstr);

        newstr = "";
        while (*pR != '\0')
        {
            newstr += *(pR++);
            if (*pR == ' ')
                return -1;
        }
        if (is_Number(newstr) == false)
        {
            delete obj;
            return -1;
        }
        obj->TIME_B = stoi(newstr);

        if (obj->TIME_B < obj->TIME_A)
        {
            delete obj;
            return -1;
        }
    }
    delete[] temp;
    //---------Xong tách chuỗi----------

    Tuyen *ptr = this->t_head;
    int numsDeletedTrip = 0;
    if (t_head == NULL)
    {
        return 0;
    }
    while (ptr != NULL)
    {
        if (ptr->TuyenSo == obj->CODE)
        {
            break;
        }
        ptr = ptr->t_next;
    }
    if (ptr == NULL)
    {
        return 0;
    }
    Chuyen *temp2 = ptr->c_head;
    Chuyen *previous = ptr->c_head;
    Chuyen *pointer_tamthoi = ptr->c_head;
    Chuyen *prev_pointer_tamthoi = pointer_tamthoi;
    Tuyen *prev_tuyen = ptr;

    while (temp2 != NULL)
    {
        // Big Case 1
        if (temp2->TIME_A == obj->TIME_A && obj->TIME_B == -1)
        {
            // start delete
            // Case 1: delete node đầu
            if (temp2 == ptr->c_head)
            {
                temp2 = temp2->c_next;
                delete previous;
                previous = temp2;
                ptr->c_head = temp2;
            }
            // Case 2: delete node cuối
            else if (temp2->c_next == NULL)
            {
                previous->c_next = temp2->c_next;
                delete temp2;
                temp2 = previous->c_next;
            }
            // Case 3: delete ở giữa
            else
            {
                previous->c_next = temp2->c_next;
                delete temp2;
                temp2 = previous->c_next;
            }
            ptr->NumberOfTripsNow--;
            numsDeletedTrip++;
        }
        // Big Case 2
        else if (temp2->TIME_A >= obj->TIME_A && temp2->TIME_A <= obj->TIME_B)
        {
            // start delete
            // Case 1: delete node đầu
            if (temp2 == ptr->c_head)
            {
                temp2 = temp2->c_next;
                delete previous;
                previous = temp2;
                ptr->c_head = temp2;
            }
            // Case 2: delete node cuối
            else if (temp2->c_next == NULL)
            {
                previous->c_next = temp2->c_next;
                delete temp2;
                temp2 = previous->c_next;
            }
            // Case 3: delete ở giữa
            else
            {
                previous->c_next = temp2->c_next;
                delete temp2;
                temp2 = previous->c_next;
            }
            ptr->NumberOfTripsNow--;
            numsDeletedTrip++;
        }
        // Big Case 3
        else if (obj->TIME_A == -1 && obj->TIME_B == -1)
        {
            while (pointer_tamthoi != NULL)
            {
                pointer_tamthoi = pointer_tamthoi->c_next;
                delete prev_pointer_tamthoi;
                prev_pointer_tamthoi = pointer_tamthoi;
                numsDeletedTrip++;
            }
            ptr->c_head = NULL;
            ptr->NumberOfTripsNow = 0;
            temp2 = NULL;
        }

        else
        {
            temp2 = temp2->c_next;
        }
    }

    if (ptr->NumberOfTripsNow == 0)
    {
        prev_tuyen->t_next = ptr->t_next;
        if (ptr == t_head)
        {
            delete ptr;
            t_head = NULL;
        }
        else
            delete ptr;
    }

    delete obj;
    return numsDeletedTrip;
}

int BusSystem::CS_4(string str)
{
    char *pR = new char[str.length() + 1];
    std::strcpy(pR, str.c_str());
    if (*pR == ' ')
        return -1;
    char *temp = pR;
    int counter = 0;
    while (*pR != '\0')
    {
        if (*pR == ' ')
            counter++;
        pR++;
    }
    if (counter > 2)
    {
        return -1;
    }
    Chuyen *obj = new Chuyen;
    pR = temp;
    if (counter == 1)
    {
        // CODE
        string newstr = "";
        while (*pR != ' ')
        {
            newstr += *(pR++);
        }
        pR++;
        if (*pR == ' ' || *pR == '\0')
        {
            delete obj;
            return -1;
        }
        obj->CODE = newstr;
        // TIME_A
        newstr = "";
        while (*pR != '\0')
        {
            newstr += *(pR++);
        }
        //pR++;
        if (is_Number(newstr) == false)
        {
            delete obj;
            return -1;
        }
        obj->TIME_A = stoi(newstr);
    }
    // CASE
    if (counter == 2)
    {
        // CODE
        string newstr = "";
        while (*pR != ' ')
        {
            newstr += *(pR++);
        }
        pR++;
        if (*pR == ' ' || *pR == '\0')
        {
            delete obj;
            return -1;
        }
        obj->CODE = newstr;
        // TIME_A
        newstr = "";
        while (*pR != ' ')
        {
            newstr += *(pR++);
        }
        pR++;
        if (*pR == ' ' || is_Number(newstr) == false || *pR == '\0')
        {
            delete obj;
            return -1;
        }
        obj->TIME_A = stoi(newstr);

        newstr = "";
        while (*pR != '\0')
        {
            newstr += *(pR++);
            if (*pR == ' ')
                return -1;
        }
        if (is_Number(newstr) == false)
        {
            delete obj;
            return -1;
        }
        obj->CASE = stoi(newstr);
        if (obj->CASE != 0 && obj->CASE != 1)
        {
            delete obj;
            return -1;
        }
    }
    delete[] temp;
    //-------Xong tách chuỗi-------

    Tuyen *ptr = this->t_head;
    int numsStarted = 0;
    if (t_head == NULL)
        return 0;
    while (ptr != NULL)
    {
        if (ptr->TuyenSo == obj->CODE)
        {
            break;
        }
        ptr = ptr->t_next;
    }
    if (ptr == NULL)
        return 0;

    Chuyen *temp3 = ptr->c_head;
    while (temp3 != NULL)
    {
        if (counter == 2)
        {
            if (temp3->TIME_A <= obj->TIME_A && temp3->TIME_B >= obj->TIME_A && temp3->CASE == obj->CASE)
            {
                numsStarted++;
            }
        }
        else
        {
            if (temp3->TIME_A <= obj->TIME_A && temp3->TIME_B >= obj->TIME_A)
            {
                numsStarted++;
            }
        }
        temp3 = temp3->c_next;
    }

    delete obj;
    return numsStarted;
}

int BusSystem::CE_5(string str)
{
    char *pR = new char[str.length() + 1];
    std::strcpy(pR, str.c_str());
    if (*pR == ' ')
        return -1;
    char *temp = pR;
    int counter = 0;
    while (*pR != '\0')
    {
        if (*pR == ' ')
            counter++;
        pR++;
    }
    if (counter > 2)
    {
        return -1;
    }
    Chuyen *obj = new Chuyen;
    pR = temp;
    if (counter == 1)
    {
        // CODE
        string newstr = "";
        while (*pR != ' ')
        {
            newstr += *(pR++);
        }
        pR++;
        if (*pR == ' ' || *pR == '\0')
        {
            delete obj;
            return -1;
        }
        obj->CODE = newstr;
        // TIME_B
        newstr = "";
        while (*pR != '\0')
        {
            newstr += *(pR++);
        }
        //pR++;
        if (is_Number(newstr) == false)
        {
            delete obj;
            return -1;
        }
        obj->TIME_B = stoi(newstr);
    }
    // CASE
    if (counter == 2)
    {
        // CODE
        string newstr = "";
        while (*pR != ' ')
        {
            newstr += *(pR++);
        }
        pR++;
        if (*pR == ' ' || *pR == '\0')
        {
            delete obj;
            return -1;
        }
        obj->CODE = newstr;
        // TIME_B
        newstr = "";
        while (*pR != ' ')
        {
            newstr += *(pR++);
        }
        pR++;
        if (*pR == ' ' || is_Number(newstr) == false || *pR == '\0')
        {
            delete obj;
            return -1;
        }
        obj->TIME_B = stoi(newstr);
        
        newstr = "";
        while (*pR != '\0')
        {
            newstr += *(pR++);
            if (*pR == ' ')
                return -1;
        }
        if (is_Number(newstr) == false)
        {
            delete obj;
            return -1;
        }
        obj->CASE = stoi(newstr);
        if (obj->CASE != 0 && obj->CASE != 1)
        {
            delete obj;
            return -1;
        }
    }
    delete[] temp;
    //-------Xong tách chuỗi-------

    Tuyen *ptr = this->t_head;
    int numsEnded = 0;
    if (t_head == NULL)
        return 0;
    while (ptr != NULL)
    {
        if (ptr->TuyenSo == obj->CODE)
            break;
        ptr = ptr->t_next;
    }
    if (ptr == NULL)
        return 0;

    Chuyen *temp4 = ptr->c_head;

    while (temp4 != NULL)
    {
        if (counter == 2)
        {
            if (temp4->TIME_B < obj->TIME_B && temp4->CASE == obj->CASE)
            {
                numsEnded++;
            }
        }
        else
        {
            if (temp4->TIME_B < obj->TIME_B)
            {
                numsEnded++;
            }
        }
        temp4 = temp4->c_next;
    }

    delete obj;
    return numsEnded;
}

string BusSystem::GS_6(string str)
{
    char *pR = new char[str.length() + 1];
    std::strcpy(pR, str.c_str());
    if (*pR == ' ')
        return "-1";
    char *temp = pR;
    int counter = 0;
    while (*pR != '\0')
    {
        if (*pR == ' ')
            counter++;
        pR++;
    }
    if (counter > 2)
    {
        return "-1";
    }
    Chuyen *obj = new Chuyen;
    pR = temp;
    if (counter == 1)
    {
        // CODE
        string newstr = "";
        while (*pR != ' ')
        {
            newstr += *(pR++);
        }
        pR++;
        if (*pR == ' ' || *pR == '\0')
        {
            delete obj;
            return "-1";
        }
        obj->CODE = newstr;
        // TIME_A
        newstr = "";
        while (*pR != '\0')
        {
            newstr += *(pR++);
        }
        //pR++;
        if (is_Number(newstr) == false)
        {
            delete obj;
            return "-1";
        }
        obj->TIME_A = stoi(newstr);
    }
    // CASE
    if (counter == 2)
    {
        // CODE
        string newstr = "";
        while (*pR != ' ')
        {
            newstr += *(pR++);
        }
        pR++;
        if (*pR == ' ' || *pR == '\0')
        {
            delete obj;
            return "-1";
        }
        obj->CODE = newstr;
        // TIME_A
        newstr = "";
        while (*pR != ' ')
        {
            newstr += *(pR++);
        }
        pR++;
        if (*pR == ' ' || is_Number(newstr) == false || *pR == '\0')
        {
            delete obj;
            return "-1";
        }
        obj->TIME_A = stoi(newstr);
        
        newstr = "";
        while (*pR != '\0')
        {
            newstr += *(pR++);
            if (*pR == ' ')
                return "-1";
        }
        if (is_Number(newstr) == false)
        {
            delete obj;
            return "-1";
        }
        obj->CASE = stoi(newstr);
        if (obj->CASE != 0 && obj->CASE != 1)
        {
            delete obj;
            return "-1";
        }
    }
    delete[] temp;
    //--------Xong tách chuỗi---------
    Tuyen *ptr = this->t_head;
    if (t_head == NULL)
        return 0;
    while (ptr != NULL)
    {
        if (ptr->TuyenSo == obj->CODE)
            break;
        ptr = ptr->t_next;
    }
    if (ptr == NULL)
        return "-1";

    Chuyen *temp5 = ptr->c_head;
    Chuyen *tamthoi = NULL;
    int min = INT32_MAX;
    int min_temp;
    bool hople = false;
    while (temp5 != NULL)
    {
        min_temp = obj->TIME_A - temp5->TIME_A;
        if (counter == 2)
        {
            if (min > min_temp && min_temp > 0 && temp5->CASE == obj->CASE)
            {
                hople = true;
                min = min_temp;
                tamthoi = temp5;
            }
        }

        else
        {
            if (min > min_temp && min_temp > 0)
            {
                hople = true;
                min = min_temp;
                tamthoi = temp5;
            }
            if (min == min_temp && temp5->CASE == 0)
            {
                tamthoi = temp5;
            }
        }
        temp5 = temp5->c_next;
    }
    if (hople == false)
        return "-1";
    return tamthoi->LP;
}

string BusSystem::GE_7(string str)
{
    char *pR = new char[str.length() + 1];
    std::strcpy(pR, str.c_str());
    if (*pR == ' ')
        return "-1";
    char *temp = pR;
    int counter = 0;
    while (*pR != '\0')
    {
        if (*pR == ' ')
            counter++;
        pR++;
    }
    if (counter > 2)
    {
        return "-1";
    }
    Chuyen *obj = new Chuyen;
    pR = temp;
    if (counter == 1)
    {
        // CODE
        string newstr = "";
        while (*pR != ' ')
        {
            newstr += *(pR++);
        }
        pR++;
        if (*pR == ' ' || *pR == '\0')
        {
            delete obj;
            return "-1";
        }
        obj->CODE = newstr;
        // TIME_B
        newstr = "";
        while (*pR != '\0')
        {
            newstr += *(pR++);
        }
        //pR++;
        if (is_Number(newstr) == false)
        {
            delete obj;
            return "-1";
        }
        obj->TIME_B = stoi(newstr);
    }
    // CASE
    if (counter == 2)
    {
        // CODE
        string newstr = "";
        while (*pR != ' ')
        {
            newstr += *(pR++);
        }
        pR++;
        if (*pR == ' ' || *pR == '\0')
        {
            delete obj;
            return "-1";
        }
        obj->CODE = newstr;
        // TIME_B
        newstr = "";
        while (*pR != ' ')
        {
            newstr += *(pR++);
        }
        pR++;
        if (*pR == ' ' || is_Number(newstr) == false || *pR == '\0')
        {
            delete obj;
            return "-1";
        }
        obj->TIME_B = stoi(newstr);
        
        newstr = "";
        while (*pR != '\0')
        {
            newstr += *(pR++);
            if (*pR == ' ')
                return "-1";
        }
        if (is_Number(newstr) == false)
        {
            delete obj;
            return "-1";
        }
        obj->CASE = stoi(newstr);
        if (obj->CASE != 0 && obj->CASE != 1)
        {
            delete obj;
            return "-1";
        }
    }
    delete[] temp;
    //--------Xong tách chuỗi---------
    Tuyen *ptr = this->t_head;
    if (t_head == NULL)
        return 0;
    while (ptr != NULL)
    {
        if (ptr->TuyenSo == obj->CODE)
            break;
        ptr = ptr->t_next;
    }
    if (ptr == NULL)
        return "-1";

    Chuyen *temp6 = ptr->c_head;
    Chuyen *tamthoi = NULL;
    int min = INT32_MAX, tre = INT32_MAX;
    int min_temp, trehon;
    bool found = false;
    while (temp6 != NULL)
    {
        min_temp = obj->TIME_B - temp6->TIME_B;
        trehon = obj->TIME_B - temp6->TIME_A;

        if (counter == 2)
        {
            if (min > min_temp && min_temp > 0 && temp6->CASE == obj->CASE)
            {
                found = true;
                min = min_temp;
                tamthoi = temp6;
            }
        }

        else
        {
            if (min > min_temp && min_temp > 0)
            {
                found = true;
                min = min_temp;
                tamthoi = temp6;
            }
            if (min == min_temp && temp6->CASE == 0)
            {
                if (tre > trehon)
                {
                    tre = trehon;
                    tamthoi = temp6;
                }
            }
        }
        temp6 = temp6->c_next;
    }
    if (found == false)
        return "-1";
    return tamthoi->LP;
}