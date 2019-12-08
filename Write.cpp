#include <iostream>

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
//     },
//    "user": "Ross"
//}


int main(int argc, char *argv[])
{
    Document doc;
    doc.SetObject();

    Document::AllocatorType& allocator = doc.GetAllocator();

    // "hello": "world"
    // 添加一个string
    Value hello("world");
    doc.AddMember("hello", hello, allocator);

    // "t": true
    // 添加一个bool
    Value t(true);
    doc.AddMember("t", t, allocator);

    // "f": false
    // 添加一个bool
    Value f(false);
    doc.AddMember("f", f, allocator);

    // "n": null
    // 添加一个NULL
    Value n;
    n.SetNull();
    doc.AddMember("n", n, allocator);

    // "i": 123
    // 添加一个int
    Value i(123);
    doc.AddMember("i", i, allocator);

    // "pi": 3.1416
    // 添加一个double
    Value pi(3.1416);
    doc.AddMember("pi", pi, allocator);

    // "arr": [1, 2, 3, 4]
    // 添加一个Array
    Value arr(kArrayType);
    arr.PushBack(1, allocator);
    arr.PushBack(2, allocator);
    arr.PushBack(3, allocator);
    arr.PushBack(4, allocator);
    doc.AddMember("arr", arr, allocator);

    // "arr2": [{"name": "xjs", "sex": "male"}, {"name": "rick", "sex": "male"}]
    // 添加一个Object Array
    Value arr2(kArrayType);
    Value obj1(kObjectType);
    obj1.AddMember("name", Value().SetString("xjs"), allocator);
    obj1.AddMember("sex", Value().SetString("male"), allocator);
    arr2.PushBack(obj1, allocator);

    Value obj2(kObjectType);
    obj2.AddMember("name", Value().SetString("rick"), allocator);
    obj2.AddMember("sex", Value().SetString("male"), allocator);
    arr2.PushBack(obj2, allocator);

    doc.AddMember("arr2", arr2, allocator);

    // "obj": {"name": "morty", "sex": "male"}
    // 添加一个Object
    Value obj3(kObjectType);
    obj3.AddMember("name", Value().SetString("morty"), allocator);
    obj3.AddMember("sex", Value().SetString("male"), allocator);
    doc.AddMember("obj", obj3, allocator);

    // "user" : "Ross"
    // 另一种添加string的方式
    Value user;
    const char* user_name = "Ross";
    size_t user_len = strlen(user_name);
    user = StringRef(user_name, user_len);
    doc.AddMember("user", user, allocator);

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    doc.Accept(writer);

    std::cout << buffer.GetString() << std::endl;
    return 0;
}