const db = require('../database');
const bcrypt = require('bcryptjs');

const card = {
  checkPassword: function (cardnum, callback) {
    return db.query(
      'SELECT pin, locked_status FROM card WHERE cardnumber=?',
      [cardnum],
      callback,
    );
  },
  setLockedStatus: function (params, callback) {
    return db.query(
      'UPDATE card SET locked_status=? WHERE cardnumber=?',
      [params.locked_status, params.cardnum],
      callback,
    );
  },
  /**
   * Get all card data, requires admin access.
   */
  getAll: function (callback) {
    return db.query(
      'SELECT idcard, cardnumber, idcustomer, type, locked_status FROM card;',
      callback,
    );
  },

  /**
   * Get card data
   * Only authenticated card owner can get data
   * @param {string} cardnumber - The card number to search for
   * @param {function} callback - The callback function to handle the query result
   * @returns {void}
   *
   * */
  getByCardnumber: function (cardnumber, callback) {
    return db.query(
      'SELECT idcard, cardnumber, idcustomer, type FROM card WHERE cardnumber=?',
      [cardnumber],
      callback,
    );
  },

  //Get card by id
  getById: function (idcard, callback) {
    return db.query('SELECT * FROM card WHERE idcard=?', [idcard], callback);
  },

  /**
   * Add a card. Requires admin access
   * @param {Object} card_data - Object with card data
   * @param {string} [cardData.cardnumber] - new cardnumber
   * @param {string} [cardData.pin] - new pin code, will be hashed
   * @param {string} [cardData.type] - new cards type
   * @param {string} [cardData.idcustomer] - The new card owner
   * @param {function} callback - callback function
   * @returns {void}
   */
  add: function (card_data, callback) {
    bcrypt.hash(card_data.pin, 10, function (err, hashed_pin) {
      return db.query(
        'INSERT INTO card(cardnumber, pin, idcustomer, type, locked_status) VALUES(?,?,?,?,?)',
        [
          card_data.cardnumber,
          hashed_pin,
          card_data.idcustomer,
          card_data.type,
          card_data.locked_status,
        ],
        callback,
      );
    });
  },

  /**
   * Updates a card in the database. Requires Admin access
   * All cardData fields are optional, old ones kept if no new ones given.
   * @param {number} idcard - The card id to change
   * @param {Object} card_data - The new card data
   * @param {string} [cardData.cardnumber] - new card number
   * @param {string} [cardData.pin] - new pin, will be hashed
   * @param {string} [cardData.type] - The card type
   * @param {number} [cardData.idcustomer] - The new card owner
   * @param {number} [cardData.locked_status] - The new locked status
   * @param {function} callback - The callback function to handle results
   * @returns {void}
   */
  update: function (idcard, card_data, callback) {
    bcrypt.hash(card_data.pin, 10, function (err, hashed_pin) {
      // TODO: Move to dynamic db call to avoid two db calls
      db.query('SELECT * FROM card WHERE idcard=?', [idcard], (err, result) => {
        if (err) {
          return callback(err);
        }
        if (!result.length) {
          return callback({ error: 'Card not found' });
        }
        const previous = result[0];

        // Updates only fields where new info is given.
        return db.query(
          'UPDATE card SET cardnumber=?, pin=?, idcustomer=?,type=? WHERE idcard=?',
          [
            card_data.cardnumber || previous.cardnumber,
            card_data.pin ? hashed_pin : previous.pin,
            card_data.idcustomer || previous.idcustomer,
            card_data.type || previous.type,
            idcard,
            card_data.locked_status || previous.locked_status,
          ],
          function (err, result) {
            if (err) {
              return callback(err);
            }

            callback(null, result);
          },
        );
      });
    });
  },

  //Remove a card
  delete: function (idcard, callback) {
    return db.query('DELETE FROM card WHERE idcard=?', [idcard], callback);
  },
};

module.exports = card;
