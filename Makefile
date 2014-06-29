MY_TARGETS = Time/ Thread/ StringUtils/ Random/ OptParse/ ConfigurationFileParser/ JSONParser/ \
			ClientServer/GenericClient/ ClientServer/GenericServer/

.PHONY: all $(MY_TARGETS)
all: $(MY_TARGETS)


all: $(MY_TARGETS)
	
$(MY_TARGETS):
	@echo ""
	@echo "   *** Making $@ ***"
	@$(MAKE) -C $@;
	
clean:
	@find . -name '*.o' -o -name '*.so' | xargs rm -v
	
