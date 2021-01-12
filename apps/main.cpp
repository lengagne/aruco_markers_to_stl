#include <iostream>
#include <fstream>
#include <regex>

std::string  GetBaseFilename(const std::string filename)
{
    size_t pos = filename.rfind(std::string("."));
    if(pos == std::string::npos)  //No extension.
        return filename;

    if(pos == 0)    //. is at the front. Not an extension.
        return filename;

    return filename.substr(0, pos);
}

using namespace std;

int main( int argc, char ** argv)
{
    std::string filename,text;
    bool print_text = false;
    if (argc == 2)
    {
        filename = argv[1];
        std::cout<<"Using filename " << filename <<std::endl;
    }else if (argc==3)
    {
        filename = argv[1];
        text = argv[2];
        print_text = true;
        std::cout<<"Using filename " << filename <<" With text: "<< text<<std::endl;
        
        if (text == "filename_extract_id")
        {
             text = "ID = "+std::regex_replace(filename,std::regex("[^0-9]*([0-9]+).*"),std::string("$1"));
            std::cout<<"extracting name from filename  text = "<<text<<std::endl;
        }
        
    }else
    {
        std::cerr<<"Error you must specify a file name " << std::endl;
        return 1;
    }
    
    double width = 1.0;
    double length = 1.0;
    double depth = 5e-3;
    
    std::cout<<"Image to stl converter using openscad"<<std::endl;
    
    // creation du fond black
    ofstream fileblack;
    fileblack.open ("black.scad");
    fileblack << " difference() \n {    \n translate([5,0,0])  cube([35,35,5],center=true); \n    translate([3,0,2.6])    scale([0.14,0.14,-1])  \n surface(file = \""<<filename<<"\", center = true);";
    if (print_text)
    {
            fileblack<<"\ntranslate([22.0,-"<< text.size()*1.2<<",-2.5])   rotate([0,0,90])  linear_extrude(6)  text (\""<<text<<"\", font=\"Ubuntu Mono:style=Bold\", $fn=50,size= 4);";
    }
    fileblack<<"\n } " <<std::endl;
    fileblack.close();

    ofstream filewhite;
    filewhite.open ("white.scad");
    if(print_text)  filewhite<<"union(){ \n translate([22.0,-"<< text.size()*1.2<<",-2.5])   rotate([0,0,90])  linear_extrude(5)  text (\""<<text<<"\", font=\"Ubuntu Mono:style=Bold\", $fn=50,size= 4); \n";
    filewhite << " intersection() \n {    \n cube([35,35,5],center=true); \n    translate([3,0,2.6])    scale([0.14,0.14,-1])  \n surface(file = \""<<filename<<"\", center = true); \n } " <<std::endl;
    if(print_text)  filewhite<<"} \n";
    filewhite.close();
    
    std::cout<<"running openscad for black file"<<std::endl;
    system("openscad -o black.stl black.scad");
    std::cout<<"running openscad for white file"<<std::endl;
    system("openscad -o white.stl white.scad");    
    
    std::string dummy = "cp black.stl " + GetBaseFilename(filename)+"_black.stl";
    system(dummy.c_str());
    dummy = "cp white.stl " + GetBaseFilename(filename)+"_white.stl";
    system(dummy.c_str());
        
    return 0;
}
