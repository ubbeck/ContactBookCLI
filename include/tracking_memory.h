#ifdef _DEBUG
     #define new new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
     #define new new
#endif
