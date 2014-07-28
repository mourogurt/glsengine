#ifndef ENGSCENE_HPP
#define ENGSCENE_HPP
#include <engValue.hpp>
#include <engShader.hpp>

class EngObject {
public:
  EngObject();
  int createAttribute();
  EngGLAttribute *getAttribute(unsigned);
  bool deleteAttribute(unsigned);
  int loadShader(std::string vsrs, std::string fsrc, std::string tcsrc = "",
                 std::string tesrc = "", std::string gsrc = "");
  bool useShader(unsigned);
  bool deleteShader(unsigned);
  void render();
  void render(unsigned, int type = GL_TRIANGLES);
  std::vector<std::string> getLog();
  std::vector<std::string> getErrLog();
  std::vector<std::string> getAttributeLog(unsigned);
  std::vector<std::string> getAttributeErrLog(unsigned);
  std::vector<std::string> getShaderLog(unsigned);
  std::vector<std::string> getShaderErrLog(unsigned);
  ~EngObject();

private:
  std::vector<EngGLAttribute> attribs;
  std::vector<EngShader> shaders;
  GLint VAO;
  Log log;
  Log errlog;
  static unsigned int binded_vao;
};

unsigned int EngObject::binded_vao = 0;

#endif // ENGSCENE_HPP
