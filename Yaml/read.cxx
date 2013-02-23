#include <std.hxx>
#include <yaml-cpp/yaml.h>
#include <CommandLineArgs/ParseArgs.hxx>

#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

typedef vector<string> StringVector;

int main (int argc, char** argv)
{
  ParseArgs pa(argc, argv);
  Args args = pa();
  fs::path yamlFile (args["cur_src_dir"]);
  yamlFile /= "test.yml";
  if (!fs::exists(yamlFile)) {
    exit (-1);
  }

  YAML::Node config = YAML::LoadFile(yamlFile.string());
  StringVector sv = config["Config"]["Genres"].as<StringVector>();
  printContainer("Genres", sv);
}
