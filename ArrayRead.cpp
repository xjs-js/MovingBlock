#include <iostream>
#include <fstream>
#include <string>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/pointer.h>

using namespace rapidjson;

int main(int argc, char *argv[]) {
    std::ifstream in;
    in.open("hello.json", std::ifstream::binary);
    if (in.is_open()) {
       std::cout << "File Opened" << std::endl;
       std::string json;
       std::string line;
       while (!in.eof()) {
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

       // method 1
       if (Value* person_1 = Pointer("/people/0").Get(doc))
       {
           printf("name => %s\n", Pointer("/people/0/name").Get(doc)->GetString());
           printf("sex => %s\n", Pointer("/people/0/sex").Get(doc)->GetString());
       }

        // method 2
        if (Value* person = Pointer("/people").Get(doc)) {
            if (person->IsArray()) {
                printf("size: %d\n", person->Size());
                const Value& arr = person->GetArray();
                for (Value::ConstValueIterator itr = arr.Begin(); itr != arr.End(); ++itr) {
                    if (itr->IsObject()) {
                        auto val = itr->GetObject();
                        if (val.HasMember("name")) {
                            const Value& name = val["name"];
                            if (name.IsString()) {
                                printf("name = %s\n", name.GetString());
                            }
                        }
                        if (val.HasMember("sex")) {
                            const Value& sex = val["sex"];
                            if (sex.IsString()) {
                                printf("sex = %s\n", sex.GetString());
                            }
                        }
                    }
                }
            }
        }

        // method 3
        std::string first_name = "/people/0/name";
        std::string first_sex = "/people/0/sex";
        if (Value* first_name_p = Pointer(first_name.c_str()).Get(doc)) {
            if (first_name_p->IsString())
                printf("name = %s\n", first_name_p->GetString());
        }
        if (Value* first_name_p = Pointer(first_name.c_str()).Get(doc)) {
            if (first_name_p->IsString())
                printf("name = %s\n", first_name_p->GetString());
        }

        // method 4
        std::string prefix = "/people/";
        int num = 2;
        for (int i = 0; i < num; ++i) {
            std::string prefix_num = prefix + std::to_string(i);
            if (Value* person = Pointer(prefix_num.c_str()).Get(doc)) {
                if (person->IsObject()) {
                    auto val = person->GetObject();
                    if (val.HasMember("name")) {
                        const Value& name = val["name"];
                        if (name.IsString()) {
                            printf("name = %s\n", name.GetString());
                        }
                    }
                    if (val.HasMember("sex")) {
                        const Value& sex = val["sex"];
                        if (sex.IsString()) {
                            printf("sex = %s\n", sex.GetString());
                        }
                    }
                }
            }
        }
    }

    return 0;
}

