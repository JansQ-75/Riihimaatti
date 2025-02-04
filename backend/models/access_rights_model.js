const db = require('../database');

const access_rights = {
 
  // get all
  getAll: function (callback) {
    return db.query('SELECT * FROM access_rights;', callback);
  },

// get by access id
  getById: function (idaccess_rights, callback) {
      return db.query(
        'SELECT * FROM access_rights WHERE idaccess_rights=?',
        [idaccess_rights],
        callback,
      );
    },

// add an access right 
add: function (access_rights_data, callback) {
  return db.query(
    'INSERT INTO access_rights(idcard, idbank_account) VALUES(?,?)',
    [
      access_rights_data.idcard,
      access_rights_data.idbank_account,
     ],
    callback,
  );
},

// delete
delete: function (idaccess_rights, callback) {
  return db.query(
    'DELETE FROM access_rights WHERE idaccess_rights=?',
    [idaccess_rights],
    callback,
  );
},
};
  module.exports = access_rights;