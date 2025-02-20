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

  // update
  update: function (idaccess_rights, access_rights_data, callback) {
    // Query to get wanted data
    db.query('SELECT * FROM access_rights WHERE idaccess_rights=?', [idaccess_rights], (err, result) => {
      if (err) {
        return callback(err);
      }
      if (!result.length) {
        return callback({ error: 'Access right not found' });
      }
      // Sets current account data values to "previous values"
      const previous = result[0];

      // Query to update account data
      // if new value isn't set, then previous value remains
      return db.query
        (
          'UPDATE access_rights SET idcard=?, idbank_account=? WHERE idaccess_rights=?',
          [
            access_rights_data.idcard || previous.idcard,
            access_rights_data.idbank_account || previous.idbank_account,
            idaccess_rights
          ],
          function (err, result) {
            if (err) {
              return callback(err);
            }

            callback(null, result);
          },
        );
    });
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