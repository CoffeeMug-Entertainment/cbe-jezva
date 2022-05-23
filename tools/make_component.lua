#!/usr/bin/lua

if #arg < 1 then
    print("USAGE:\nmake_component [component name]")
end

local COMPONENT_STRING =
[[
    #ifndef {1}_HPP
    #define {1}_HPP

#include "Component.hpp"

class {0} : public Component {
	public:
		{0}();
		~{0}();
		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() override;
};

{0}::{0}(){}
~{0}::{0}(){}

#endif
]]

local first_step = COMPONENT_STRING:gsub("{0}", arg[1])
local second_step = first_step:gsub("{1}", string.upper(arg[1]))

local header_file = io.open(arg[1] .. ".hpp", "w")
header_file:write(second_step)