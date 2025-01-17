const db = require('../database');
const bcrypt = require('bcryptjs');

const card = {
  checkPassword: function (cardnum, callback) {
    return db.query(
      'SELECT pin FROM card WHERE cardnumber=?',
      [cardnum],
      callback,
    );
  },
};

module.exports = card;
