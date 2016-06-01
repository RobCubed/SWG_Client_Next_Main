#!/usr/bin/perl

# This script helps create loader.plsql.

$header = "N";

print "-- GENERATED PLSQL FOLLOWS\n";
print "-- generated by makeloader.pl\n\n";

while (<>)
{
	if (/create table (\w+)_objects/)
    {
	$tablename = $1;
	

	&parseTable($tablename);
	
	$procname = $tablename;
	$procname =~ s/harvester\_installation/harvester\_inst/g;
	$procname =~ s/manufacture\_installation/manufacture\_inst/g;
	$procname =~ s/manufacture\_schematic/manf\_schematic/g;

	if ($header eq "Y")
		{
			&printLoadFuncHeader($tablename);
		}
		else
		{
			&printLoadFuncBody($tablename);
		}

	reset columns;
    }

    if (/create table objects/)
    {
	$tablename = "object";
	&parseTable($tablename);
	reset columns;
    }
}

sub parseTable
{

   my ($line);

   while (!/\;/)
    {

	if ((!/key/) && (!/object_id/) && (/^\s+(\w+\s+\w.*)/) && (!/\-\-\s*NO_BIND/))
	{
		$line = $1;
		/(\w+\s+\w+)/;
 	    push(@columns,$1);
		
	}
	$_=<>;
    }
}

sub printLoadFuncBody
{
    my($tablename)=@_;
    my($notfirst, $name, $type);

  print "\tfunction load_${procname}_object\treturn cursortype\n\tas\n\t\tresult_cursor cursortype;\n\tbegin\n";
  print "\t\topen result_cursor for\n\t\t\tselect ";

  if ($tablename eq "player")
  {	print "/*+ ORDERED USE_NL(T) USE_NL(A)*/\n"; }
  else
  {	print "/*+ ORDERED USE_NL(T) */\n"; }

  print "\t\t\t\tt.object_id";
	foreach $column (@columns)
  {
		($name,$type)=split(" ",$column);
		if (!($tablename eq "player" and $name eq "num_lots"))
  	{	print ",\n";
   		print "\t\t\t\tt.$name";
   	}

  	if ($tablename eq "player" and $name eq "station_id")
		{
			print ",\n\t\t\t\ta.house_id,\n ";
			print "\t\t\t\ta.num_lots,\n ";
			print "\t\t\t\ta.is_outcast,\n ";
			print "\t\t\t\ta.cheater_level,\n ";
			print "\t\t\t\ta.max_lots_adjustment";
		}

  }

    print "\n\t\t\tfrom\n\t\t\t\tobject_list l,\n";
    print "\t\t\t\t${tablename}_objects t";

	if ($tablename eq "player")
	{ print ",\n\t\t\t\taccounts a\n";
 		print "\t\t\twhere t.station_id = a.station_id and\n";
	}
	else
 	{	print "\n\t\t\twhere\n";

  }
    print "\t\t\t\tt.object_id=l.object_id;\n\n";
    print "\t\treturn result_cursor;\n\tend;\n\n";

}


sub printLoadFuncHeader
{
    my($tablename)=@_;
    my($notfirst,$name,$type, $i);

    print "\tfunction\tload_${procname}_object\t\t\treturn cursortype;\n";
}

