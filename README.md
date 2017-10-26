## radosgw-admin

### Get the code

	git clone https://github.com/bugosiphionah/radosgw-admin
	cd radosgw-admin

### Compile

**Manually**

	g++ -I/home/programming/Desktop/Projects/radosgw-admin/boost/boost radosgw-admin.cpp -o radosgw-admin -lboost_program_options

Note the path to boost folder in project

**Use Cmake (Require Edits to CMakeLists.txt)**

Point to your boost setup files in the CMakeLists.txt by replacing the paths in the lines:

	set(Boost_INCLUDE_DIR /usr/local/src/boost_1_46_1)
	set(Boost_LIBRARY_DIR /usr/local/src/boost_1_46_1/stage/lib)
	
To your relevant setup paths

Then Compile

	cmake .
	make


### Execute the commands

0.help

	./radosgw-admin --help

1.Create user

	./radosgw-admin user create --uid=Seena --display-name=pbugosi --email=bugosip@gmail.com

2.Delete user

	.radosgw-admin user delete --uid=Seena

3.User Info

	./radosgw-admin user info --uid=Seena

