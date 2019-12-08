#include <iostream>
#include <fstream>

// rapidjson
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/pointer.h>

// QT
#include <QString>
using namespace rapidjson;

//{
//    "hello": "world",
//    "t": true ,
//    "f": false,
//    "n": null,
//    "i": 123,
//    "pi": 3.1416,
//    "arr": [1, 2, 3, 4],
//    "arr2" : [
//        {
//            "name" : "xjs",
//            "sex" : "male"
//        },
//        {
//            "name" : "rick",
//            "sex" : "male"
//        }],
//    "obj": {
//        "name": "morty",
//        "sex": "male"
//     }
//}


int main(int argc, char *argv[])
{
    std::ifstream in;
    in.open("hello.json", std::ifstream::binary);
    if (in.is_open())
    {
        std::cout << "File Opened" << std::endl;
        std::string json;
        std::string line;
        while (!in.eof())
        {
            getline(in, line);
            json += line;
        }
        Document doc;
        doc.Parse(json.c_str());

        // 输出原始的json内容
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        doc.Accept(writer);
        std::cout << buffer.GetString() << std::endl;

        // 读取字符串
        if (Value* hello = Pointer("/hello").Get(doc))
        {
            printf("hello = %s\n", hello->GetString());
        }

        // 读取bool值
        if (Value* t = Pointer("/t").Get(doc))
        {
            printf("t = %s\n", t->GetBool() ? "true" : "false");
        }

        // 读取bool值
        if (Value* f = Pointer("/f").Get(doc))
        {
            printf("f = %s\n", f->GetBool() ? "true" : "false");
        }

        // 读取null
        if (Value* n = Pointer("/n").Get(doc))
        {
            printf("n = %s\n", n->IsNull() ? "null" : "notnull");
        }

        // 读取int
        if (Value* i = Pointer("/i").Get(doc))
        {
            printf("i = %d\n", i->GetInt());
        }

        // 读取double
        if (Value* pi = Pointer("/pi").Get(doc))
        {
            printf("pi = %f\n", pi->GetDouble());
        }

        // 读取Array
        if (Value* arr = Pointer("/arr").Get(doc))
        {
            if (arr->IsArray())
            {
                size_t arr_num = arr->Size();

                for (size_t i = 0; i < arr_num; ++i)
                {
                    QString q_i = QString::number(i);
                    QString key = "/arr/" + q_i;

                    if (Value* val = Pointer(key.toStdString().c_str()).Get(doc))
                    {
                        printf("arr[%d] = %d\n", i, val->GetInt());
                    }
                }
            }
        }

        // 读取Object Array，太复杂了，直接写了
        if (Value* arr2_0_name = Pointer("/arr2/0/name").Get(doc))
        {
            if (Value* arr2_0_sex = Pointer("/arr2/0/sex").Get(doc))
            {
                printf("{name: %s, sex: %d}\n", arr2_0_name->GetString(), arr2_0_sex->GetString());
            }
        }
        if (Value* arr2_1_name = Pointer("/arr2/1/name").Get(doc))
        {
            if (Value* arr2_1_sex = Pointer("/arr2/1/sex").Get(doc))
            {
                printf("{name: %s, sex: %d}\n", arr2_1_name->GetString(), arr2_1_sex->GetString());
            }
        }

        // 读取Object
        printf("obj: {");
        if (const Value* name = GetValueByPointer(doc, "/obj/name"))
        {
            if (name->IsString())
            {
                printf("name: %s,", name->GetString());
            }
        }
        if (const Value* sex = GetValueByPointer(doc, "/obj/sex"))
        {
            if (sex->IsString())
            {
                printf("sex: %s,", sex->GetString());
            }
        }
        printf("}");
    }
}