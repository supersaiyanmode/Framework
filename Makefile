MY_TARGETS = Time/ Thread/ StringUtils/ Random/ OptParse/ ConfigurationFileParser/ JSONParser/ \
			ClientServer/GenericServer/ ClientServer/HTTPServer ClientServer/CMSServer/Server \
			ClientServer/CMSServer/Client ClientServer/CMSServer/Test

.PHONY: all $(MY_TARGETS)
all: $(MY_TARGETS)


all: $(MY_TARGETS)
	
$(MY_TARGETS):
	echo "Making $@"
	@$(MAKE) -C $@;
	
clean:
	@find . -name '*.o' -o -name '*.so' | xargs rm -v
	
