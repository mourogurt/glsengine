.PHONY: clean All

All:
	@echo "----------Building project:[ glfwclass - Debug ]----------"
	@cd "glfwclass" && $(MAKE) -f  "glfwclass.mk"
clean:
	@echo "----------Cleaning project:[ glfwclass - Debug ]----------"
	@cd "glfwclass" && $(MAKE) -f  "glfwclass.mk" clean
