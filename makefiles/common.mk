source_dir := ../source
dest_dir := ../lib/$(CONFIGURATION)

sources := $(wildcard $(source_dir)/*)
source_names := $(patsubst $(source_dir)/%,%,$(sources))
object_names := $(patsubst %.cpp,%.o,$(filter %.cpp,$(source_names)))
objects := $(patsubst %,$(dest_dir)/%,$(object_names))

$(dest_dir)/libcppexts.a: $(objects)
	rm -f $@
	ar -r -s $@ $?

$(objects): $(sources)
	@mkdir -p $(dest_dir)
	$(CXX) $(CXXFLAGS) -c $(patsubst $(dest_dir)/%.o,$(source_dir)/%.cpp,$@) -o $@

clean:
	rm -f -r $(dest_dir)
