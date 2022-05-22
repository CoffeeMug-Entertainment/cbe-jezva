#!/usr/bin/python3

import sys

COMPONENT_TEXT = """
#ifndef {1}_HPP
#define {1}_HPP

#include "Component.hpp"

class {0} : public Component {{
	public:
		{0}();
		~{0}();
		void Initialize() override;
		void Update([[maybe_unused]] float deltaTime) override;
		void Render() override;
}};

{0}::{0}(){{}}
~{0}::{0}(){{}}

#endif
"""

def print_usage():
    print("USAGE:\nmake_component [component name]");

def main():

    if len(sys.argv) < 2:
        print_usage()
        return
    
    comp_name = sys.argv[1]
    with open(comp_name + ".hpp", "w") as header_file:
        header_file.write(COMPONENT_TEXT.format(comp_name, comp_name.upper()))

if __name__ == '__main__':
    main()