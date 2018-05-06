

#define GET_SET(TypeName,VarName,FunName) \
						protected:TypeName VarName;\
						public:TypeName get##FunName()const{ return VarName; }\
							      void set##FunName(TypeName _Value){VarName = _Value;}
						