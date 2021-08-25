function typeObj(obj){
      var type=Object.prototype.toString.call(obj);
      if(type==="[object Array]"){
        return "array"
      }else if(type==="[object Object]"){
        return "object"
      }else{
        return typeof(obj)
      }
}

function findMemberValue(_json,_key,_index){
    if(typeObj(_json)!=="object"&&typeObj(_json)!=="array"){
        console.log("_json is not json object or array!")
        return
    }
    if(_key===undefined){
        console.log("_key undefined!")
        return}
    var index=Object.keys(_json).indexOf(_key.toString())
    if(index>=0){//找到
        if(_index!==undefined){
            return Object.values(_json)[index][_index]
        }
        return Object.values(_json)[index]
    }
    var valuelist=Object.values(_json)
//    console.log(valuelist)
    var res=undefined
    for(let ov in valuelist){
//        console.log(typeObj(valuelist[ov]),valuelist[ov])
        if(typeObj(valuelist[ov])==="object"||
                typeObj(valuelist[ov])==="array"){
            res= findMemberValue(valuelist[ov],_key,_index)
            if(res!==undefined){
                return res
            }
        }
    }
    return
}
function findMemberValueEx(_json,_conditions,_index){
    if(typeObj(_json)!=="object"&&typeObj(_json)!=="array"){
        console.log("Ex _json is not json object or array!")
        return
    }
    var tobj=_json;
    if(typeObj(_conditions)==="object"||typeObj(_conditions)==="array"){
        for(let i in _conditions){
            tobj=findMemberValue(tobj,_conditions[i.toString()])
            if(tobj===undefined){
                return
            }
        }
    }else{
         tobj=findMemberValue(tobj,_conditions)
    }
    if(_index!==undefined){
        tobj=tobj[_index]
    }
    return tobj
}

function setMemberValue(_json,_key,_value,_index){
    if(typeObj(_json)!=="object"&&typeObj(_json)!=="array"){
        console.log("_json is not json object or array!")
        return undefined
    }
    var index=Object.keys(_json).indexOf(_key.toString())
//    console.log(_key ,index)
    var tindex=Object.keys(_json).indexOf(_key)
//    console.log(_key ,tindex)
    if(_key===undefined){return undefined}
    if(index>=0){//找到
        if(_index!==undefined){
            _json[_key][_index]=_value
            return 1
        }
        _json[_key]=_value
        return 2
    }
    var valuelist=Object.values(_json)
//    console.log(valuelist)
    var res=undefined
    for(let ov in valuelist){
//        console.log(typeObj(valuelist[ov]),valuelist[ov])
        if(typeObj(valuelist[ov])==="object"||
                typeObj(valuelist[ov])==="array"){
            res= setMemberValue(valuelist[ov],_key,_value,_index)
            if(res!==undefined){
               return res
            }
        }
    }
    return undefined
}
function setMemberValueEx(_json,_key,_value,_conditions,_index){
    if(typeObj(_json)!=="object"&&typeObj(_json)!=="array"){
        console.log("_json is not json object or array!")
        return
    }
    var tobj=_json;
    if(_conditions !==undefined){
        tobj=findMemberValueEx(tobj,_conditions)
        if(typeObj(tobj)!=="object"&&typeObj(tobj)!=="array"){
            console.log("tobj is not json object or array!")
            return
        }
    }
//    console.log(tobj,_key,_value,_index)
    return setMemberValue(tobj,_key,_value,_index)
}

function addMemberValue(_json,_parent,_key,_value){
    if(typeObj(_json)!=="object"&&typeObj(_json)!=="array"){
        console.log("_json is not json object or array!")
        return undefined
    }
    if(_key===undefined){return undefined}
    if(_parent===undefined||_parent===""){
        _json[_key]=_value;
        return 1;
    }

    var index=Object.keys(_json).indexOf(_parent.toString())
    if(index>=0){//找到
        if(typeObj(_json[_parent])==="array"){//数组
            _json[_parent].push(_value)
            return 1
        }
        //对象
        _json[_parent][_key]=_value
        return 2
    }
    var valuelist=Object.values(_json)
//    console.log(valuelist)
    var res=undefined
    for(let ov in valuelist){
//        console.log(typeObj(valuelist[ov]),valuelist[ov])
        if(typeObj(valuelist[ov])==="object"||
                typeObj(valuelist[ov])==="array"){
            res= addMemberValue(valuelist[ov],_parent,_key,_value)
            if(res!==undefined){
                return res
            }
        }
    }
    return undefined
}
function addMemberValueEx(_json,_parent,_key,_value,_conditions){
    if(typeObj(_json)!=="object"&&typeObj(_json)!=="array"){
        console.log("_json is not json object or array!")
        return
    }
    var tobj=_json;
    var ret=undefined
    if(_conditions !==undefined){
        tobj=findMemberValueEx(tobj,_conditions)
        if(typeObj(tobj)!=="object"&&typeObj(tobj)!=="array"){
            return
        }
    }
    return addMemberValue(tobj,_parent,_key,_value)
}

function removeMemberValue(_json,_key,_index){
    if(typeObj(_json)!=="object"&&typeObj(_json)!=="array"){
        console.log("_json is not json object or array!")
        return undefined
    }
    if(_key===undefined){return undefined}
    var index=Object.keys(_json).indexOf(_key.toString())
    if(index>=0){//找到
        if(_index!==undefined){
            _json[_key][_index]=undefined
            if(typeObj(_json[_key])==="array"){
                _json[_key].splice(_index,1)
            }
            return 1
        }
        _json[_key]=undefined
        return 2
    }
    var valuelist=Object.values(_json)
//    console.log(valuelist)
    var res=undefined
    for(let ov in valuelist){
//        console.log(typeObj(valuelist[ov]),valuelist[ov])
        if(typeObj(valuelist[ov])==="object"||
                typeObj(valuelist[ov])==="array"){
            res= removeMemberValue(valuelist[ov],_key,_index)
            if(res!==undefined){
               return res
            }
        }
    }
    return undefined
}
function removeMemberValueEx(_json,_key,_conditions,_index){
    if(typeObj(_json)!=="object"&&typeObj(_json)!=="array"){
        console.log("_json is not json object or array!")
        return
    }
    var tobj=_json;
    if(_conditions !==undefined){
        tobj=findMemberValueEx(tobj,_conditions)
//        console.log(tobj)
        if(typeObj(tobj)!=="object"&&typeObj(tobj)!=="array"){
            return
        }
    }
    return removeMemberValue(tobj,_key,_index)
}

function testMyJson(){
    var json ={
        "a0":0,
        "b0":{"a1":1},
        "c0":{"b1":{"a2":2,"b2":3},"c1":4},
        "d0":{"b1":{"a2":12,"b2":13},"c1":14},
        "e0":[0,1,2,3,4],
        "f0":{"e1":[0,1,2,3,4],"f1":4},
        "g0":{"g1":[[0,1,2,3,4],
                    [10,11,12,13,14],
                    [20,21,22,23,24],
                    [30,31,32,33,34],
                    [40,41,42,43,44]
                   ],"f1":4},
        "h0":{"h1":[{"c2":0,"d2":1},
                    {"c2":10,"d2":11},
                    {"c2":20,"d2":21},
                    {"c2":30,"d2":31},]},
    }
    console.log(JSON.stringify(json))

    console.log("*******************************")
    console.log(">>>>>Find MemBer Value<<<<<")
    console.log("findMemberValue(a0):" ,findMemberValue(json,"a0"));
    console.log("findMemberValue(b2):" ,findMemberValue(json,"b2"));
    console.log("findMemberValueEx(d0->b2):" ,findMemberValueEx(json,["d0","b2"]));
    console.log("findMemberValue(e0[3]):" ,findMemberValue(json,"e0",3));
    console.log("findMemberValue(e1[3]):" ,findMemberValue(json,"e1",3));
    console.log("findMemberValueEx(g1[3][2])1:" ,findMemberValueEx(json,["g1",3],2));
    console.log("findMemberValueEx(g1[3][2])2:" ,findMemberValueEx(json,["g1",3,2]));
    console.log("findMemberValue(d2):" ,findMemberValue(json,"d2"));
    console.log("findMemberValueEx(h1[1]->d2):" ,findMemberValueEx(json,["h1",1,"d2"]));

    console.log("*******************************")
    console.log(">>>>>Set MemBer Value<<<<<")
    console.log("setMemberValue(a0) res:" ,setMemberValue(json,"a0",111));
    console.log("setMemberValue(a0) json:" ,JSON.stringify(json));
    console.log("setMemberValue(b2):" ,setMemberValue(json,"b2",111));
    console.log("setMemberValue(b2) json:" ,JSON.stringify(json));
    console.log("setMemberValueEx(d0->b2):" ,setMemberValueEx(json,"b2",111,["d0"]));
    console.log("setMemberValueEx(d0->b2) json:" ,JSON.stringify(json));
    console.log("setMemberValue(e0[3]):" ,setMemberValue(json,"e0",111,3));
    console.log("setMemberValue(e0[3]) json:" ,JSON.stringify(json));
    console.log("setMemberValue(e1[3]):" ,setMemberValue(json,"e1",111,3));
    console.log("setMemberValue(e1[3]) json:" ,JSON.stringify(json));
    console.log("setMemberValueEx(e1[3]):" ,setMemberValueEx(json,"e1",222,null,3));
    console.log("setMemberValueEx(e1[3]) json:" ,JSON.stringify(json));
    console.log("setMemberValueEx(g1[3][2])):" ,setMemberValueEx(json,2,111,["g1",3]));
    console.log("setMemberValueEx(g1[3][2])) json:" ,JSON.stringify(json));
    console.log("setMemberValue(d2):" ,setMemberValue(json,"d2",111));
    console.log("setMemberValue(d2) json:" ,JSON.stringify(json));
    console.log("setMemberValueEx(h1[1]->d2):" ,setMemberValueEx(json,"d2",111,["h1",2]));
    console.log("setMemberValueEx(h1[1]->d2)) json:" ,JSON.stringify(json));

    console.log("*******************************")
    console.log(">>>>>Add MemBer Value<<<<<")
    console.log("addMemberValue() res:" ,addMemberValue(json,"","z1",666));
    console.log("addMemberValue() json:" ,JSON.stringify(json));
    console.log("addMemberValue(b1) res:" ,addMemberValue(json,"b1","z1",666));
    console.log("addMemberValue(b1) json:" ,JSON.stringify(json));
    console.log("addMemberValueEx(d0->b1) res:" ,addMemberValueEx(json,"b1","z1",666,["d0"]));
    console.log("addMemberValueEx(d0->b1) json:" ,JSON.stringify(json));
    console.log("addMemberValue(e0) res:" ,addMemberValue(json,"e0","z1",666));
    console.log("addMemberValue(e0) json:" ,JSON.stringify(json));
    console.log("addMemberValue(e1) res:" ,addMemberValue(json,"e1","z1",666));
    console.log("addMemberValue(e1) json:" ,JSON.stringify(json));
    console.log("addMemberValueEx(g1[3]) res:" ,addMemberValueEx(json,3,"z1",666,["g1"]));
    console.log("addMemberValueEx(g1[3]) json:" ,JSON.stringify(json));
    console.log("addMemberValueEx(h1[2])1 res:" ,addMemberValueEx(json,2,"z1",666,["h1"]));
    console.log("addMemberValueEx(h1[2])1 json:" ,JSON.stringify(json));
    console.log("addMemberValueEx(h1[2])2 res:" ,addMemberValueEx(json,"","z1",666,["h1",2]));
    console.log("addMemberValueEx(h1[2])2 json:" ,JSON.stringify(json));

    console.log("*******************************")
    console.log(">>>>>Remove MemBer Value<<<<<")
    console.log("removeMemberValue() res:" ,removeMemberValue(json,"z1"));
    console.log("removeMemberValue() json:" ,JSON.stringify(json));
    console.log("removeMemberValueEx(d0->z1) res:" ,removeMemberValueEx(json,"z1",["d0"]));
    console.log("removeMemberValueEx(d0->z1) json:" ,JSON.stringify(json));
    console.log("removeMemberValue(e0[5]) res:" ,removeMemberValue(json,"e0",5));
    console.log("removeMemberValue(e0[5]) json:" ,JSON.stringify(json));
    console.log("removeMemberValue(e1[5]) res:" ,removeMemberValue(json,"e1",5));
    console.log("removeMemberValue(e1[5]) json:" ,JSON.stringify(json));
    console.log("removeMemberValueEx(g1[3][5]) res:" ,removeMemberValueEx(json,3,["g1"],5));
    console.log("removeMemberValueEx(g1[3][5]) json:" ,JSON.stringify(json));
    console.log("removeMemberValueEx(h1[2]->z1) res:" ,removeMemberValueEx(json,"z1",["h1",2]));
    console.log("removeMemberValueEx(h1[2]->z1) json:" ,JSON.stringify(json));

}
