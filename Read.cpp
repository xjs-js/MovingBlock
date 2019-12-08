#include <iostream>
#include <fstream>

// rapidjson
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

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
//        }
//    ],
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
        std::cout << json << std::endl;
        Document doc;
        doc.Parse(json.c_str());

        // 输出原始的json内容
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        doc.Accept(writer);
        std::cout << buffer.GetString() << std::endl;


        // 最顶层是一个Object
        assert(doc.IsObject());

        assert(doc.HasMember("hello"));
        assert(doc["hello"].IsString());
        printf("hello = %s\n", doc["hello"].GetString());

        assert(doc.HasMember("t"));
        assert(doc["t"].IsBool());
        printf("t = %s\n", doc["t"].GetBool() ? "true" : "false");

        assert(doc.HasMember("f"));
        assert(doc["f"].IsBool());
        printf("f = %s\n", doc["f"].GetBool() ? "true" : "false");

        assert(doc.HasMember("n"));
        printf("n = %s\n", doc["n"].IsNull() ? "null" : "?");

        assert(doc.HasMember("i"));
        assert(doc["i"].IsNumber());
        printf("i = %d\n", doc["i"].GetInt());

        assert(doc.HasMember("pi"));
        assert(doc["pi"].GetDouble());
        printf("pi = %g\n", doc["pi"].GetDouble());

        // 数组
        assert(doc.HasMember("arr"));
        const Value& arr = doc["arr"];
        // 通过索引
        for (SizeType i = 0; i < arr.Size(); ++i)
        {
            printf("arr[%d] = %d\n", i, arr[i].GetInt());
        }

        // 对象数组
        assert(doc.HasMember("arr2"));
        Value& arr2 = doc["arr2"];
        if (arr2.IsArray())
        {
            for (size_t i = 0; i < arr2.Size(); ++i)
            {
                Value& elem = arr2[i];
                if(elem.IsObject())
                {
                    if (elem.HasMember("name"))
                    {
                        const Value& name = elem["name"];
                        if (name.IsString())
                        {
                            printf("name = %s\n", name.GetString());
                        }
                        const Value& sex = elem["sex"];
                        if (sex.IsString())
                        {
                            printf("name = %s\n", sex.GetString());
                        }
                    }
                }

            }
        }

        // 存储一个对象
        assert(doc.HasMember("obj"));
        Value& obj = doc["obj"];
        if (obj.IsObject())
        {
            if (obj.HasMember("name"))
            {
                const Value& name = obj["name"];
                if (name.IsString())
                {
                    printf("name = %s\n", name.GetString());
                }
            }
            if (obj.HasMember("sex"))
            {
                const Value& sex = obj["sex"];
                if (sex.IsString())
                {
                    printf("sex = %s\n", sex.GetString());
                }
            }
        }
    }
}