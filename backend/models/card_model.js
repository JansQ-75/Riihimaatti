const db = require('../database');
const bcrypt = require('bcryptjs');

const card = {
  checkPassword: function (cardnum, callback) {
    return db.query(
      'SELECT pin FROM card WHERE cardnumber=?',
      [cardnum],
      callback,
    );
    
  //Get all card data
  getAll: function (callback) {
    return db.query('SELECT * FROM card;', callback);
  },

  //Get card by id
  getById: function (idcard, callback) {
    return db.query('SELECT * FROM card WHERE idcard=?', [idcard], callback);
  },

  //Add a card
  add: function (card_data, callback) {
    bcrycpt.hash(card_data.pin, 10, function (err, hashed_pin) {
      return db.query(
        'INSERT INTO card(cardnumber, pin, idcustomer, type) VALUES(?,?,?,?)',
        [
          card_data.cardnumber,
          hashed_pin,
          card_data.idcustomer,
          card_data.type,
        ],
        callback,
      );
    });
  },

  //Update a card
  update: function (idcard, card_data, callback) {
    bcrycpt.hash(card_data.pin, 10, function (err, hashed_pin) {
      return db.query(
        'UPDATE card SET cardnumber=?, pin=?, idcustomer=?,type=? WHERE idcard=?',
        [
          card_data.cardnumber,
          hashed_pin,
          card_data.idcustomer,
          card_data.type,
          idcard,
        ],
        callback,
      );
    });
  },

  //Remove a card
  delete: function (idcard, callback) {
    return db.query('DELETE FROM card WHERE idcard=?', [idcard], callback);
  },
};

module.exports = card;
