#define BOOST_TEST_MODULE subcommand options
#include "boost/program_options.hpp"

#include <errno.h>
#include <iostream>
#include <sstream>
#include <string>

namespace 
{ 
  const size_t ERROR_IN_COMMAND_LINE = 1; 
  const size_t SUCCESS = 0; 
  const size_t ERROR_UNHANDLED_EXCEPTION = 2; 
 
}

void usage()
{
  std::cout << "usage: radosgw-admin <cmd> [options...]" << std::endl;
  std::cout << "commands:\n";
  std::cout << "  user create                create a new user\n" ;
  std::cout << "  user modify                modify user\n";
  std::cout << "  user info                  get user info\n";
  std::cout << "  user rm                    remove user\n";
  std::cout << "  user suspend               suspend a user\n";
  std::cout << "  user enable                re-enable user after suspension\n";
  std::cout << "  user check                 check user info\n";
  std::cout << "  user stats                 show user stats as accounted by quota subsystem\n";
  std::cout << "  user list                  list users\n";
  std::cout << "  caps add                   add user capabilities\n";
  std::cout << "  caps rm                    remove user capabilities\n";
  std::cout << "  subuser create             create a new subuser\n" ;
  std::cout << "  subuser modify             modify subuser\n";
  std::cout << "  subuser rm                 remove subuser\n";
  std::cout << "  key create                 create access key\n";
  std::cout << "  key rm                     remove access key\n";
  std::cout << "  bucket list                list buckets\n";
  std::cout << "  bucket limit check         show bucket sharding stats\n";
  std::cout << "  bucket link                link bucket to specified user\n";
  std::cout << "  bucket unlink              unlink bucket from specified user\n";
  std::cout << "  bucket stats               returns bucket statistics\n";
  std::cout << "  bucket rm                  remove bucket\n";
  std::cout << "  bucket check               check bucket index\n";
  std::cout << "  bucket reshard             reshard bucket\n";
  std::cout << "  bucket sync disable        disable bucket sync\n";
  std::cout << "  bucket sync enable         enable bucket sync\n";
  std::cout << "  bi get                     retrieve bucket index object entries\n";
  std::cout << "  bi put                     store bucket index object entries\n";
  std::cout << "  bi list                    list raw bucket index entries\n";
  std::cout << "  object rm                  remove object\n";
  std::cout << "  object stat                stat an object for its metadata\n";
  std::cout << "  object unlink              unlink object from bucket index\n";
  std::cout << "  objects expire             run expired objects cleanup\n";
  std::cout << "  period delete              delete a period\n";
  std::cout << "  period get                 get period info\n";
  std::cout << "  period get-current         get current period info\n";
  std::cout << "  period pull                pull a period\n";
  std::cout << "  period push                push a period\n";
  std::cout << "  period list                list all periods\n";
  std::cout << "  period update              update the staging period\n";
  std::cout << "  period commit              commit the staging period\n";
  std::cout << "  quota set                  set quota params\n";
  std::cout << "  quota enable               enable quota\n";
  std::cout << "  quota disable              disable quota\n";
  std::cout << "  global quota get           view global quota params\n";
  std::cout << "  global quota set           set global quota params\n";
  std::cout << "  global quota enable        enable a global quota\n";
  std::cout << "  global quota disable       disable a global quota\n";
  std::cout << "  realm create               create a new realm\n";
  std::cout << "  realm delete               delete a realm\n";
  std::cout << "  realm get                  show realm info\n";
  std::cout << "  realm get-default          get default realm name\n";
  std::cout << "  realm list                 list realms\n";
  std::cout << "  realm list-periods         list all realm periods\n";
  std::cout << "  realm remove               remove a zonegroup from the realm\n";
  std::cout << "  realm rename               rename a realm\n";
  std::cout << "  realm set                  set realm info (requires infile)\n";
  std::cout << "  realm default              set realm as default\n";
  std::cout << "  realm pull                 pull a realm and its current period\n";
  std::cout << "  zonegroup add              add a zone to a zonegroup\n";
  std::cout << "  zonegroup create           create a new zone group info\n";
  std::cout << "  zonegroup default          set default zone group\n";
  std::cout << "  zonegroup delete           delete a zone group info\n";
  std::cout << "  zonegroup get              show zone group info\n";
  std::cout << "  zonegroup modify           modify an existing zonegroup\n";
  std::cout << "  zonegroup set              set zone group info (requires infile)\n";
  std::cout << "  zonegroup remove           remove a zone from a zonegroup\n";
  std::cout << "  zonegroup rename           rename a zone group\n";
  std::cout << "  zonegroup list             list all zone groups set on this cluster\n";
  std::cout << "  zonegroup placement list   list zonegroup's placement targets\n";
  std::cout << "  zonegroup placement add    add a placement target id to a zonegroup\n";
  std::cout << "  zonegroup placement modify modify a placement target of a specific zonegroup\n";
  std::cout << "  zonegroup placement rm     remove a placement target from a zonegroup\n";
  std::cout << "  zonegroup placement default  set a zonegroup's default placement target\n";
  std::cout << "  zone create                create a new zone\n";
  std::cout << "  zone delete                delete a zone\n";
  std::cout << "  zone get                   show zone cluster params\n";
  std::cout << "  zone modify                modify an existing zone\n";
  std::cout << "  zone set                   set zone cluster params (requires infile)\n";
  std::cout << "  zone list                  list all zones set on this cluster\n";
  std::cout << "  zone rename                rename a zone\n";
  std::cout << "  zone placement list        list zone's placement targets\n";
  std::cout << "  zone placement add         add a zone placement target\n";
  std::cout << "  zone placement modify      modify a zone placement target\n";
  std::cout << "  zone placement rm          remove a zone placement target\n";
  std::cout << "  pool add                   add an existing pool for data placement\n";
  std::cout << "  pool rm                    remove an existing pool from data placement set\n";
  std::cout << "  pools list                 list placement active set\n";
  std::cout << "  policy                     read bucket/object policy\n";
  std::cout << "  log list                   list log objects\n";
  std::cout << "  log show                   dump a log from specific object or (bucket + date\n";
  std::cout << "                             + bucket-id)\n";
  std::cout << "                             (NOTE: required to specify formatting of date\n";
  std::cout << "                             to \"YYYY-MM-DD-hh\")\n";
  std::cout << "  log rm                     remove log object\n";
  std::cout << "  usage show                 show usage (by user, date range)\n";
  std::cout << "  usage trim                 trim usage (by user, date range)\n";
  std::cout << "  gc list                    dump expired garbage collection objects (specify\n";
  std::cout << "                             --include-all to list all entries, including unexpired)\n";
  std::cout << "  gc process                 manually process garbage\n";
  std::cout << "  lc list                    list all bucket lifecycle progress\n";
  std::cout << "  lc process                 manually process lifecycle\n";
  std::cout << "  metadata get               get metadata info\n";
  std::cout << "  metadata put               put metadata info\n";
  std::cout << "  metadata rm                remove metadata info\n";
  std::cout << "  metadata list              list metadata info\n";
  std::cout << "  mdlog list                 list metadata log\n";
  std::cout << "  mdlog trim                 trim metadata log (use start-date, end-date or\n";
  std::cout << "                             start-marker, end-marker)\n";
  std::cout << "  mdlog status               read metadata log status\n";
  std::cout << "  bilog list                 list bucket index log\n";
  std::cout << "  bilog trim                 trim bucket index log (use start-marker, end-marker)\n";
  std::cout << "  datalog list               list data log\n";
  std::cout << "  datalog trim               trim data log\n";
  std::cout << "  datalog status             read data log status\n";
  std::cout << "  opstate list               list stateful operations entries (use client_id,\n";
  std::cout << "                             op_id, object)\n";
  std::cout << "  opstate set                set state on an entry (use client_id, op_id, object, state)\n";
  std::cout << "  opstate renew              renew state on an entry (use client_id, op_id, object)\n";
  std::cout << "  opstate rm                 remove entry (use client_id, op_id, object)\n";
  std::cout << "  replicalog get             get replica metadata log entry\n";
  std::cout << "  replicalog update          update replica metadata log entry\n";
  std::cout << "  replicalog delete          delete replica metadata log entry\n";
  std::cout << "  orphans find               init and run search for leaked rados objects (use job-id, pool)\n";
  std::cout << "  orphans finish             clean up search for leaked rados objects\n";
  std::cout << "  orphans list-jobs          list the current job-ids for orphans search\n";
  std::cout << "  role create                create a AWS role for use with STS\n";
  std::cout << "  role delete                delete a role\n";
  std::cout << "  role get                   get a role\n";
  std::cout << "  role list                  list roles with specified path prefix\n";
  std::cout << "  role modify                modify the assume role policy of an existing role\n";
  std::cout << "  role-policy put            add/update permission policy to role\n";
  std::cout << "  role-policy list           list policies attached to a role\n";
  std::cout << "  role-policy get            get the specified inline policy document embedded with the given role\n";
  std::cout << "  role-policy delete         delete policy attached to a role\n";
  std::cout << "  reshard add                schedule a resharding of a bucket\n";
  std::cout << "  reshard list               list all bucket resharding or scheduled to be reshared\n";
  std::cout << "  reshard process            process of scheduled reshard jobs\n";
  std::cout << "  reshard cancel             cancel resharding a bucket\n";
  std::cout << "options:\n";
  std::cout << "   --tenant=<tenant>         tenant name\n";
  std::cout << "   --uid=<id>                user id\n";
  std::cout << "   --subuser=<name>          subuser name\n";
  std::cout << "   --access-key=<key>        S3 access key\n";
  std::cout << "   --email=<email>\n";
  std::cout << "   --secret/--secret-key=<key>\n";
  std::cout << "                             specify secret key\n";
  std::cout << "   --gen-access-key          generate random access key (for S3)\n";
  std::cout << "   --gen-secret              generate random secret key\n";
  std::cout << "   --key-type=<type>         key type, options are: swift, s3\n";
  std::cout << "   --temp-url-key[-2]=<key>  temp url key\n";
  std::cout << "   --access=<access>         Set access permissions for sub-user, should be one\n";
  std::cout << "                             of read, write, readwrite, full\n";
  std::cout << "   --display-name=<name>\n";
  std::cout << "   --max-buckets             max number of buckets for a user\n";
  std::cout << "   --admin                   set the admin flag on the user\n";
  std::cout << "   --system                  set the system flag on the user\n";
  std::cout << "   --bucket=<bucket>\n";
  std::cout << "   --pool=<pool>\n";
  std::cout << "   --object=<object>\n";
  std::cout << "   --date=<date>\n";
  std::cout << "   --start-date=<date>\n";
  std::cout << "   --end-date=<date>\n";
  std::cout << "   --bucket-id=<bucket-id>\n";
  std::cout << "   --shard-id=<shard-id>     optional for mdlog list\n";
  std::cout << "                             required for: \n";
  std::cout << "                               mdlog trim\n";
  std::cout << "                               replica mdlog get/delete\n";
  std::cout << "                               replica datalog get/delete\n";
  std::cout << "   --metadata-key=<key>      key to retrieve metadata from with metadata get\n";
  std::cout << "   --remote=<remote>         zone or zonegroup id of remote gateway\n";
  std::cout << "   --period=<id>             period id\n";
  std::cout << "   --epoch=<number>          period epoch\n";
  std::cout << "   --commit                  commit the period during 'period update'\n";
  std::cout << "   --staging                 get staging period info\n";
  std::cout << "   --master                  set as master\n";
  std::cout << "   --master-url              master url\n";
  std::cout << "   --master-zonegroup=<id>   master zonegroup id\n";
  std::cout << "   --master-zone=<id>        master zone id\n";
  std::cout << "   --rgw-realm=<name>        realm name\n";
  std::cout << "   --realm-id=<id>           realm id\n";
  std::cout << "   --realm-new-name=<name>   realm new name\n";
  std::cout << "   --rgw-zonegroup=<name>    zonegroup name\n";
  std::cout << "   --zonegroup-id=<id>       zonegroup id\n";
  std::cout << "   --zonegroup-new-name=<name>\n";
  std::cout << "                             zonegroup new name\n";
  std::cout << "   --rgw-zone=<name>         name of zone in which radosgw is running\n";
  std::cout << "   --zone-id=<id>            zone id\n";
  std::cout << "   --zone-new-name=<name>    zone new name\n";
  std::cout << "   --source-zone             specify the source zone (for data sync)\n";
  std::cout << "   --default                 set entity (realm, zonegroup, zone) as default\n";
  std::cout << "   --read-only               set zone as read-only (when adding to zonegroup)\n";
  std::cout << "   --placement-id            placement id for zonegroup placement commands\n";
  std::cout << "   --tags=<list>             list of tags for zonegroup placement add and modify commands\n";
  std::cout << "   --tags-add=<list>         list of tags to add for zonegroup placement modify command\n";
  std::cout << "   --tags-rm=<list>          list of tags to remove for zonegroup placement modify command\n";
  std::cout << "   --endpoints=<list>        zone endpoints\n";
  std::cout << "   --index-pool=<pool>       placement target index pool\n";
  std::cout << "   --data-pool=<pool>        placement target data pool\n";
  std::cout << "   --data-extra-pool=<pool>  placement target data extra (non-ec) pool\n";
  std::cout << "   --placement-index-type=<type>\n";
  std::cout << "                             placement target index type (normal, indexless, or #id)\n";
  std::cout << "   --compression=<type>      placement target compression type (plugin name or empty/none)\n";
  std::cout << "   --tier-type=<type>        zone tier type\n";
  std::cout << "   --tier-config=<k>=<v>[,...]\n";
  std::cout << "                             set zone tier config keys, values\n";
  std::cout << "   --tier-config-rm=<k>[,...]\n";
  std::cout << "                             unset zone tier config keys\n";
  std::cout << "   --sync-from-all[=false]   set/reset whether zone syncs from all zonegroup peers\n";
  std::cout << "   --sync-from=[zone-name][,...]\n";
  std::cout << "                             set list of zones to sync from\n";
  std::cout << "   --sync-from-rm=[zone-name][,...]\n";
  std::cout << "                             remove zones from list of zones to sync from\n";
  std::cout << "   --fix                     besides checking bucket index, will also fix it\n";
  std::cout << "   --check-objects           bucket check: rebuilds bucket index according to\n";
  std::cout << "                             actual objects state\n";
  std::cout << "   --format=<format>         specify output format for certain operations: xml,\n";
  std::cout << "                             json\n";
  std::cout << "   --purge-data              when specified, user removal will also purge all the\n";
  std::cout << "                             user data\n";
  std::cout << "   --purge-keys              when specified, subuser removal will also purge all the\n";
  std::cout << "                             subuser keys\n";
  std::cout << "   --purge-objects           remove a bucket's objects before deleting it\n";
  std::cout << "                             (NOTE: required to delete a non-empty bucket)\n";
  std::cout << "   --sync-stats              option to 'user stats', update user stats with current\n";
  std::cout << "                             stats reported by user's buckets indexes\n";
  std::cout << "   --show-log-entries=<flag> enable/disable dump of log entries on log show\n";
  std::cout << "   --show-log-sum=<flag>     enable/disable dump of log summation on log show\n";
  std::cout << "   --skip-zero-entries       log show only dumps entries that don't have zero value\n";
  std::cout << "                             in one of the numeric field\n";
  std::cout << "   --infile=<file>           specify a file to read in when setting data\n";
  std::cout << "   --state=<state string>    specify a state for the opstate set command\n";
  std::cout << "   --replica-log-type        replica log type (metadata, data, bucket), required for\n";
  std::cout << "                             replica log operations\n";
  std::cout << "   --categories=<list>       comma separated list of categories, used in usage show\n";
  std::cout << "   --caps=<caps>             list of caps (e.g., \"usage=read, write; user=read\")\n";
  std::cout << "   --yes-i-really-mean-it    required for certain operations\n";
  std::cout << "   --warnings-only           when specified with bucket limit check, list\n";
  std::cout << "                             only buckets nearing or over the current max\n";
  std::cout << "                             objects per shard value\n";
  std::cout << "   --bypass-gc               when specified with bucket deletion, triggers\n";
  std::cout << "                             object deletions by not involving GC\n";
  std::cout << "   --inconsistent-index      when specified with bucket deletion and bypass-gc set to true,\n";
  std::cout << "                             ignores bucket index consistency\n";
  std::cout << "\n";
  std::cout << "<date> := \"YYYY-MM-DD[ hh:mm:ss]\"\n";
  std::cout << "\nQuota options:\n";
  std::cout << "   --bucket                  specified bucket for quota command\n";
  std::cout << "   --max-objects             specify max objects (negative value to disable)\n";
  std::cout << "   --max-size                specify max size (in B/K/M/G/T, negative value to disable)\n";
  std::cout << "   --quota-scope             scope of quota (bucket, user)\n";
  std::cout << "\nOrphans search options:\n";
  std::cout << "   --pool                    data pool to scan for leaked rados objects in\n";
  std::cout << "   --num-shards              num of shards to use for keeping the temporary scan info\n";
  std::cout << "   --orphan-stale-secs       num of seconds to wait before declaring an object to be an orphan (default: 86400)\n";
  std::cout << "   --job-id                  set the job id (for orphans find)\n";
  std::cout << "   --max-concurrent-ios      maximum concurrent ios for orphans find (default: 32)\n";
  std::cout << "\nOrphans list-jobs options:\n";
  std::cout << "   --extra-info              provide extra info in job list\n";
  std::cout << "\nRole options:\n";
  std::cout << "   --role-name               name of the role to create\n";
  std::cout << "   --path                    path to the role\n";
  std::cout << "   --assume-role-policy-doc  the trust relationship policy document that grants an entity permission to assume the role\n";
  std::cout << "   --policy-name             name of the policy document\n";
  std::cout << "   --policy-doc              permission policy document\n";
  std::cout << "   --path-prefix             path prefix for filtering roles\n";
  std::cout << "\n";
}

int main(int argc, char **argv)
{
    namespace po = boost::program_options;

    po::options_description commands("Global options");
    commands.add_options()
        ("help", "Display this help")
        ("user", po::value<std::string>(), "user command to execute")
        ("subargs", po::value<std::vector<std::string> >(), "Arguments for user command");

    po::positional_options_description pos;
    pos.add("user", 1).
        add("subargs", -1);

    po::variables_map vm;

    po::parsed_options parsed = po::command_line_parser(argc, argv).
        options(commands).
        positional(pos).
        allow_unregistered().
        run();

    po::store(parsed, vm);

    if (vm.count("help")){
        usage();
        return SUCCESS;
    }

    std::string cmd = vm["user"].as<std::string>();

    if (cmd == "user")
    {
        //Create User
        po::options_description create_desc("create options");
        create_desc.add_options()
            ("uid", po::value<std::string>(), "User ID")
            ("create", po::value<std::string>(), "User ID")
            ("display-name", po::value<std::string>(), "Display Name")
            ("email", po::value<std::string>(), "email");
        try 
        { 

            po::positional_options_description positionalOptions; 
            positionalOptions.add("create", 1);  
     
       
            std::vector<std::string> opts = po::collect_unrecognized(parsed.options, po::include_positional);
            opts.erase(opts.begin());

            po::store(po::command_line_parser(opts).options(create_desc).positional(positionalOptions).run(), vm);
            
            std::string cmd = vm["create"].as<std::string>();
            po::notify(vm); 
            if (cmd == "create"){

                std::cout << "user created with uid:";
                std::cout << "  " << vm["uid"].as<std::string>() << "\n";
                std::cout << "display-name:  " << vm["display-name"].as<std::string>() << "\n";
                std::cout << "and email: " << vm["email"].as<std::string>() << "\n";
                return SUCCESS; 
            }

            if (cmd == "delete"){

                std::cout << "Deleted user with uid:";
                std::cout << "  " << vm["uid"].as<std::string>() << "\n";

                return SUCCESS; 
            }

             if (cmd == "info"){

                std::cout << "Info for uid:";
                std::cout << "  " << vm["uid"].as<std::string>() << "\n";

                return SUCCESS; 
            }
           
        } 
        catch(boost::program_options::required_option& e) 
        { 
          printf("fail");
        } 
    }

}