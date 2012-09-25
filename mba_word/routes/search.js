var fs = require('fs');

function load_file(filename){
    var content = fs.readFileSync(filename).toString();
    if (!content) {
        console.log("cannot get the content\n");
        return null;
    }
    var array = content.split("\n");
    var length = array.length;

    var key;
    var value;
    var database = new Array();
    for (var i = 0; i < length; i++) {
        if (i % 3 == 0) {
            key = array [i].split(" ").shift();
        } else if (i % 3 == 1) {
            value = array [i];
        } else {
            database.push({w: key, a: value});
        }
    }

    return database;
};

function find_word(db, query){
    if (!db) {
        return null;
    }
    var length = db.length;
    var reg = new RegExp('^'+query);
    var array = new Array();
    var got = false;
    for (var i = 0; i < db.length; i++) {
        if (reg.test(db[i].w)) {
            if (!got)
                got = true;
            array.push(db[i]);
        } else if (got) {
            /* as mba5500 already sorted. make it faster */
            break;
        }
    }
    return array;
};

var db = null;
exports.search = function(req, res){
    if (db == null)
        db = load_file ("./data/mba5500");
    console.log (db.length);
    var array = find_word (db, req.params.word);
    res.render('index', { title: array[0].w })
};

var array = find_word(db, "res");
